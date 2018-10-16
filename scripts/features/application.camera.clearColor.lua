FEATURE main.lua/Impl
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
registerApplicationCameraClearColorProperty(applicationCameraMT)
