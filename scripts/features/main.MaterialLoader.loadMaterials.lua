FEATURE main.lua/Impl
loadMaterials = function(self, definition)
    print("TODO", "loadMaterials()")

    -- Load shader resources.
    local resources = render.materialsDefinitionToShaderResources(definition)
    for _, resource in pairs(resources)
    do
        local group = resource[1]
        local vertex = resource[2]
        local fragment = resource[3]
        io.write(
            string.format("Loading shader resource '%s/%s'\n", group, vertex)
        )
        self.__resourcePool:loadResource(group, vertex)
        io.write(
            string.format("Loading shader resource '%s/%s'\n", group, fragment)
        )
        self.__resourcePool:loadResource(group, fragment)
    end


    --[[

    local materials = {}
    local materialCopies = {}

    -- Split definitions into fully specified materials and copies that
    -- reference other materials.


    for name, parameters in pairs(definition)
    do
        print("material", name)

        for parameterName, parameter in pairs(parameters)
        do
            print("", "parameter", parameterName)

        end

    end

    --]]
 
end,
