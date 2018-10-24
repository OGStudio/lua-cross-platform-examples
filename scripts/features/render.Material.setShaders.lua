FEATURE main.lua/Impl
setShaders = function(self, vertex, fragment)
    local key = "application.materialPool.material.setShaders"
    ENV:call(
        key,
        {
            self.__name,
            vertex.__group,
            vertex.__name,
            fragment.__group,
            fragment.__name
        }
    )
end,
