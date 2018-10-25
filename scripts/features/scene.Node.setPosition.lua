FEATURE main.lua/Impl
setPosition = function(self, position)
    local key = "application.nodePool.node.setPosition"
    local node = self.__name
    ENV:call(
        key,
        {
            node,
            position[1],
            position[2],
            position[3],
        }
    )
end,
