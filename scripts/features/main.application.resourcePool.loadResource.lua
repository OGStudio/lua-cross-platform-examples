FEATURE main.lua/Impl
main.application.resourcePool.loadResource = function(self, groupName, resourceName)
    local key = "application.resourcePool.loadResource"
    ENV:call(key, {groupName, resourceName})
end
