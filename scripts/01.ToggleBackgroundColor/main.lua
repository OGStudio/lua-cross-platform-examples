
--[[
This file is part of Lua cross-platform examples:
  https://github.com/OGStudio/lua-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
--]]

-- Library domain begins --

-- createPropertiesMetatable Start
function createPropertiesMetatable()
    local mt =
    {
        -- Register properties with callbacks.
        callbacks = {},
        register = function(mtself, key, getter, setter)
            local callback = {}
            callback.getter = getter
            callback.setter = setter
            mtself.callbacks[key] = callback
        end,

        -- Getter.
        __index = function(self, key)
            local mtself = getmetatable(self)
            local callback = mtself.callbacks[key]
            if 
                callback and
                callback.getter
            then
                return callback.getter(self)
            end
            return nil
        end,

        -- Setter.
        __newindex = function(self, key, value)
            local mtself = getmetatable(self)
            local callback = mtself.callbacks[key]
            if 
                callback and
                callback.setter
            then
                callback.setter(self, value)
            end
        end,
    }
    return mt
end
-- createPropertiesMetatable End
-- createReporter Start
-- NOTE This is an (osgcpe::)core::Reporter (C++) adaptation to Lua.
function createReporter()
    local reporter =
    {
        -- Internal list of callbacks.
        __callbacks = {},

        -- Add a new callback.
        addCallback = function(self, callback, name)
            -- Work around callback reactivation happenning
            -- before `report()` call.
            if (self:__reactivateInactiveCallback(name))
            then
                return
            end
            local item = {
                callback = callback,
                name = name
            }
            table.insert(self.__callbacks, item)
        end,

        -- Internal list of one-time callbacks.
        __oneTimeCallbacks = {},

        -- Add a callback that is only executed once.
        addOneTimeCallback = function(self, callback)
            table.insert(self.__oneTimeCallbacks, callback)
        end,

        -- Internal list of callback names to remove later.
        __inactiveCallbackNames = {},

        removeCallback = function(self, name)
            -- This call only deactivates a callback for
            -- later removal that happens during next report() call.
            for callback in self.__callbacks
            do
                if 
                    callback.name and
                    (callback.name == name)
                then
                    table.insert(self.__inactiveCallbackNames, name)
                end
            end
        end,

        report = function(self)
            self:__removeInactiveCallbacks()
            
            -- Call normal callbacks.
            for callback in self.__callbacks
            do
                callback.callback()
            end

            -- Create a copy of the list of one-time callbacks.
            local oneTimeCallbacks = {table.unpack(self.__oneTimeCallbacks)}
            -- Remove one-time callbacks.
            self.__oneTimeCallbacks = {}
            -- Call one-time callbacks.
            for callback in oneTimeCallbacks
            do
                callback()
            end
        end,

        __reactivateInactiveCallback = function(self, name)
            for id, callbackName in pairs(self.__inactiveCallbackNames)
            do
                if (callbackName == name)
                then
                    self.__inactiveCallbackNames[id] = nil
                    return true
                end
            end
            return false
        end,

        __removeInactiveCallbacks = function(self)
            -- Loop through the names of inactive callbacks.
            for name in self.__inactiveCallbackNames
            do
                -- Loop through callbacks to find matching name.
                for id, callback in self.__callbacks
                do
                    if 
                        callback.name and
                        (callback.name == name)
                    then
                        -- Remove matching callback.
                        self.__callbacks[id] = nil
                        break
                    end
                end
            end
            -- Clear the list of the names of inactive callbacks.
            self.__inactiveCallbackNames = {}
        end,
    }
    return reporter
end
-- createReporter End

-- application Start
application = {}
-- application End
-- application.camera Start
application.camera = {}
local applicationCameraMetatable = createPropertiesMetatable()
setmetatable(application.camera, applicationCameraMetatable)
-- application.camera End
-- application.camera.clearColor Start
local function registerApplicationCameraClearColorProperty(mt)
    local shortKey = "clearColor"
    local key = "application.camera." .. shortKey
    mt:register(
        shortKey,
        function(self)
            return ENV:call(key, {})
        end,
        function(self, value)
            ENV:call(key, value)
        end
    )
end
registerApplicationCameraClearColorProperty(applicationCameraMetatable)
-- application.camera.clearColor End
-- application.mouse Start
-- Create mouse.
application.mouse = {
    position = {},
    pressedButtons = {},
}

-- Configure it.
do
    local mouse = application.mouse
    -- Create and configure environment client.
    local client = EnvironmentClient.new()
    -- Define keys.
    local buttonsKey = "application.mouse.pressedButtons"
    local positionKey = "application.mouse.position"
    -- Define methods.
    client.respondsToKey = function(key)
        return
            (key == buttonsKey) or
            (key == positionKey)
    end
    client.call = function(key, values)
        if (key == buttonsKey)
        then
            mouse.pressedButtons = values
            print("accepted mouse pressed buttons")
        elseif (key == positionKey)
        then
            mouse.position = values
            print("accepted mouse position")
        end

        return {}
    end

    -- Register client.
    application.mouse.client = client
    ENV:addClient(application.mouse.client);
end
-- application.mouse End

-- Library domain ends --

-- Example domain begins --

-- testBackgroundColorToggle Start
local function testBackgroundColorToggle(camera)
    print("TODO Toggle background color")

    local color = camera.clearColor
    print("Previous background color:", color[1], color[2], color[3])

    -- Set new color.
    camera.clearColor = {0.5, 0.5, 0.5}

    color = camera.clearColor
    print("Current background color:", color[1], color[2], color[3])
end

testBackgroundColorToggle(application.camera)
-- testBackgroundColorToggle End

-- Example domain ends --

