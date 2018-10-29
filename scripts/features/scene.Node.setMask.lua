FEATURE main.lua/Impl
setMask = function(self, mask)
    local key = "application.nodePool.node.setMask"
    local node = self.__name
    ENV:call(key, {node, mask})
end,
