
application = {}

application.camera = {}

local clearColorKey = "clearColor"
local applicationCameraClearColorKey = "application.camera.clearColor"

-- clearColor property.
local clearColorMT =
{
    -- Getter.
    __index = function(table, key)
        if (key == clearColorKey) then
            return ENV:call(applicationCameraClearColorKey, {})
        end
        return nil
    end,

    -- Setter.
    __newindex = function(table, key, value)
        if (key == clearColorKey) then
            ENV:call(applicationCameraClearColorKey, value)
        end
    end,
}
setmetatable(application.camera, clearColorMT)

print("Set background color")

local color = application.camera.clearColor
print("Current bg color", color[1], color[2], color[3])
application.camera.clearColor = {0.5, 0.5, 0.5}

