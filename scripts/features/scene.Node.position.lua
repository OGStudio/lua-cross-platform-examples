FEATURE main.lua/Impl
do
    local shortKey = "position"
    local key = "application.nodePool.node." .. shortKey
    propertiesMT:register(
        shortKey,
        function(self)
            local node = self.__name
            return ENV:call(key, {node})
        end,
        function(self, position)
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
        end
    )
end
