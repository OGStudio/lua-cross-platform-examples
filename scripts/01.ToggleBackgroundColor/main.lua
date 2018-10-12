
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
                return callback.getter()
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
                callback.setter(value)
            end
        end,
    }
    return mt
end
-- createPropertiesMetatable End

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
        function()
            return ENV:call(key, {})
        end,
        function(value)
            ENV:call(key, value)
        end
    )
end
registerApplicationCameraClearColorProperty(applicationCameraMetatable)
-- application.camera.clearColor End

-- Library domain ends --

-- Example domain begins --

-- toggleBackgroundColor Start
local function toggleBackgroundColor(camera)
    print("TODO Toggle background color")

    local color = camera.clearColor
    print("Previous background color:", color[1], color[2], color[3])

    -- Set new color.
    camera.clearColor = {0.5, 0.5, 0.5}

    color = camera.clearColor
    print("Current background color:", color[1], color[2], color[3])
end

toggleBackgroundColor(application.camera)
-- toggleBackgroundColor End

-- Example domain ends --
