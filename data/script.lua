
application = {}

application.camera = {}

function createPropertiesMetatable()
    local mt =
    {
        callbacks = {},
        -- Register property with callbacks.
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

local cameraProperties = createPropertiesMetatable()
local clearColorKey = "clearColor"
local applicationCameraClearColorKey = "application.camera.clearColor"
cameraProperties:register(
    "clearColor", 
    -- Getter.
    function()
        return ENV:call(applicationCameraClearColorKey, {})
    end,
    -- Setter.
    function(values)
        ENV:call(applicationCameraClearColorKey, values)
    end
)

setmetatable(application.camera, cameraProperties)

print("Set background color")

local color = application.camera.clearColor
print("Current bg color", color[1], color[2], color[3])
application.camera.clearColor = {0.5, 0.5, 0.5}

