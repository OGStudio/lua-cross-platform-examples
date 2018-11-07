FEATURE main.lua/Impl
removeFromParents = function(self)
    local key = "application.nodePool.node.removeFromParents"
    ENV:call(key, {self.__name})
end,
