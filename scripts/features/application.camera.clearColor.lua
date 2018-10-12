FEATURE main.lua
local function registerApplicationCameraClearColorProperty(mt)
    local shortKey = "clearColor"
    local key = "application.camera." + shortKey
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

