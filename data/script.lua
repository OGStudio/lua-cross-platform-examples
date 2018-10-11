
application = {}

camera = {}
application.camera = camera

-- clearColor property.
local clearColorMT =
{
    -- Getter.
    __index = function(table, key)
        if (key == "clearColor") then
            return ENV:call("application.camera.clearColor", {})
        end
        return nil
    end,
    -- Setter.
    __newindex = function(table, key, value)
        if (key == "clearColor") then
            ENV:call("application.camera.clearColor", value)
        end
    end,
}
setmetatable(camera, clearColorMT)

print("Set background color")

local color = application.camera.clearColor
print("Current bg color", color[1], color[2], color[3])
application.camera.clearColor = {0.5, 0.5, 0.5}

