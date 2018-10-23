
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

core = {}

-- core.PropertiesMT Start
function core.createPropertiesMT()
    local instance = {
        -- Register properties with callbacks.
        __callbacks = {},
        register = function(mtself, key, getter, setter)
            local callback = {}
            callback.getter = getter
            callback.setter = setter
            mtself.__callbacks[key] = callback
        end,

        -- Getter.
        __index = function(self, key)
            local mtself = getmetatable(self)
            local callback = mtself.__callbacks[key]
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
            local callback = mtself.__callbacks[key]
            if 
                callback and
                callback.setter
            then
                callback.setter(self, value)
            end
        end,
    }
    return instance
end
-- core.PropertiesMT End
-- core.Reporter Start
-- NOTE This is a core::Reporter (C++) implementation in Lua.
function core.createReporter()
    local instance = {
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
            for _, callback in pairs(self.__callbacks)
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
            for _, callback in pairs(self.__callbacks)
            do
                callback.callback()
            end

            -- Create a copy of the list of one-time callbacks.
            local oneTimeCallbacks = {table.unpack(self.__oneTimeCallbacks)}
            -- Remove one-time callbacks.
            self.__oneTimeCallbacks = {}
            -- Call one-time callbacks.
            for _, callback in pairs(oneTimeCallbacks)
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
            for _, name in pairs(self.__inactiveCallbackNames)
            do
                -- Loop through callbacks to find matching name.
                for id, callback in pairs(self.__callbacks)
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
    return instance
end
-- core.Reporter End

resource = {}

-- resource.Resource Start
-- NOTE This is only a wrapper for a resource at C++ side.
-- NOTE This does NOT create anything at C++ side.
function resource.createResource(group, name)
    local instance = {
        __group = group,
        __name = name,

-- resource.Resource End
-- resource.Resource Start
    }
    return instance
end
-- resource.Resource End

scene = {}

-- scene.Node Start
-- NOTE This is only a wrapper for a valid node at C++ side.
-- NOTE This does NOT create anything at C++ side.
function scene.createNode(name)
    local instance = {
        __name = name,

-- scene.Node End
        -- scene.Node.addChild Start
        addChild = function(self, node)
            local key = "application.scene.node.addChild"
            local parent = self.__name
            local child = node.__name
            ENV:call(key, {parent, child})
        end,
        -- scene.Node.addChild End
-- scene.Node Start
    }
    return instance
end
-- scene.Node End

main = {}

-- main.application Start
main.application = {}
-- main.application End
-- main.application.camera Start
main.application.camera = {}
local cameraMT = core.createPropertiesMT()
setmetatable(main.application.camera, cameraMT)
-- main.application.camera End
-- main.application.parameters Start
main.application.parameters = {}
-- Transfer parameters from C++ to Lua.
do
    -- NOTE params = [key1, value1, key2, value2, ...].
    local params = ENV:call("application.parameters", {})
    local count = #params / 2
    for i = 1, count
    do
        local id = i * 2 - 1
        local key = params[id]
        local value = params[id + 1]
        main.application.parameters[key] = value
    end
end
-- main.application.parameters End
-- main.application.resourcePool Start
-- Crate resource pool.
main.application.resourcePool = {
    -- Report when loaded all requested resources.
    finishedLoading = core.createReporter(),
}

-- Configure resource pool.
do
    local pool = main.application.resourcePool
    -- Create environment client.
    local client = EnvironmentClient.new()
    -- Define finish keys.
    local finishKey = "application.resourcePool.finishedLoading"
    -- Define callback.
    client.call = function(key, values)
        if (key == finishKey)
        then
            pool.finishedLoading:report()
        end

        return {}
    end
    -- Register client.
    pool.client = client
    ENV:addClient(
        pool.client,
        {
            finishKey
        }
    );
end
-- main.application.resourcePool End
-- main.application.resourcePool.loadResource Start
main.application.resourcePool.loadResource = function(self, groupName, resourceName)
    local key = "application.resourcePool.loadResource"
    ENV:call(key, {groupName, resourceName})
end
-- main.application.resourcePool.loadResource End
-- main.application.resourcePool.resource Start
function main.application.resourcePool.resource(self, group, name)
    local key = "application.resourcePool.resource.exists"
    -- Find out if resource exists in C++.
    local result = ENV:call(key, {group, name})
    -- Return nothing if resource does not exist.
    if (not result[1]) then
        return nil
    end
    -- Return Lua representation if resource exists in C++.
    return resource.createResource(group, name)
end
-- main.application.resourcePool.resource End
-- main.application.resourcePool.setLocations Start
main.application.resourcePool.setLocations = function(self, locations)
    local key = "application.resourcePool.locations"
    ENV:call(key, locations)
end
-- main.application.resourcePool.setLocations End
-- main.application.scene Start
main.application.scene = {}
--local sceneMT = core.createPropertiesMT()
--setmetatable(main.application.scene, sceneMT)
-- main.application.scene End
-- main.application.scene.createSphere Start
main.application.scene.createSphere = function(self, name, radius)
    local key = "application.scene.createSphere"
    ENV:call(key, {name, radius})
    return scene.createNode(name)
end
-- main.application.scene.createSphere End
-- main.application.scene.node Start
function main.application.scene.node(self, name)
    local key = "application.scene.node.exists"
    -- Find out if node exists in C++.
    local result = ENV:call(key, {name})
    -- Return nothing if node does not exist.
    if (not result[1]) then
        return nil
    end
    -- Return Lua node representation if node exists in C++.
    return scene.createNode(name)
end
-- main.application.scene.node End
-- main.application.mouse Start
-- Create mouse.
main.application.mouse = {
    position = {},
    positionChanged = core.createReporter(),

    pressedButtons = {},
    pressedButtonsChanged = core.createReporter(),
}

-- Configure mouse.
do
    local mouse = main.application.mouse
    -- Create environment client.
    local client = EnvironmentClient.new()
    -- Define keys.
    local buttonsKey = "application.mouse.pressedButtons"
    local positionKey = "application.mouse.position"
    -- Define callback.
    client.call = function(key, values)
        if (key == buttonsKey)
        then
            mouse.pressedButtons = values
            mouse.pressedButtonsChanged:report()
        elseif (key == positionKey)
        then
            mouse.position = values
            mouse.positionChanged:report()
        end

        return {}
    end
    -- Register client.
    mouse.client = client
    ENV:addClient(
        mouse.client,
        {
            buttonsKey,
            positionKey
        }
    );
end
-- main.application.mouse End

-- Library domain ends --

-- Example domain begins --

-- testColorfulNodes Start
do
    -- Make sure data directory has been specified.
    local dataDir = main.application.parameters["data"]
    if (dataDir == nil)
    then
        print(
            "ERROR",
            "You must specify data directory with `--data=/path/to/data`"
        )
        return
    end

    -- Define distinct setup stages.
    function createSphereNode(scene)
        local name = "sphere"
        local radius = 1
        local sphere = scene:createSphere(name, radius)
        local root = scene:node("root")
        root:addChild(sphere)
    end
    function loadResources(resourcePool, dataDir)
        -- Specify resource locations in the lookup order.
        resourcePool:setLocations({
            dataDir
        })
        -- Load resources.
        resourcePool:loadResource(
            "shaders",
            "plain.vert"
        )
        resourcePool:loadResource(
            "shaders",
            "plain.frag"
        )
    end
    function areResourcesValid(resourcePool)
        -- Make sure all resources have been loaded successfully.
        local shaderVert = resourcePool:resource("shaders", "plain.vert")
        local shaderFrag = resourcePool:resource("shaders", "plain.frag")
        print("shaderFrag", shaderFrag)
        print("shaderVert", shaderVert)
        if (
            (shaderVert == nil) or
            (shaderFrag == nil)
        ) then
            print("ERROR", "Could not load one or more shaders")
            return false
        end

        return true
    end
    function finishSetup(resourcePool)
        print("TODO Paint the node with single-color shader")
        -- TODO Paint the node with single-color shader.

    end

    -- TODO Use nodePool
    local scene = main.application.scene
    createSphereNode(scene)

    local resourcePool = main.application.resourcePool
    print("Loading resources...")
    loadResources(resourcePool, dataDir)

    print("Finished loading resources")
    if (areResourcesValid(resourcePool))
    then
        finishSetup(resourcePool)
    end
end
-- testColorfulNodes End

-- Example domain ends --

