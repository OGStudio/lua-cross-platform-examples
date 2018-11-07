FEATURE main.lua/Impl
removeChild = function(self, node)
    local key = "application.nodePool.node.removeChild"
    local parent = self.__name
    local child = node.__name
    ENV:call(key, {parent, child})
end,
