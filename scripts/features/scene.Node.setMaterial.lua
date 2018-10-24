FEATURE main.lua/Impl
setMaterial = function(self, material)
    local key = "application.nodePool.node.setMaterial"
    local node = self.__name
    ENV:call(key, {node, material.__name})
end,
