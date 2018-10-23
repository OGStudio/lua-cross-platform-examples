FEATURE main.lua/Impl
main.application.nodePool.createSphere = function(self, name, radius)
    local key = "application.nodePool.createSphere"
    ENV:call(key, {name, radius})
    return scene.createNode(name)
end
