FEATURE main.lua/Impl
main.application.resourcePool.setLocations = function(self, locations)
    local key = "application.resourcePool.locations"
    ENV:call(key, locations)
end
