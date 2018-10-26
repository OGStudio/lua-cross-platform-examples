FEATURE main.lua/Impl
main.application.nodePool.createNode = function(self, name)
    local key = "application.nodePool.createNode"
    ENV:call(key, {name})
    return scene.createNode(name)
end
