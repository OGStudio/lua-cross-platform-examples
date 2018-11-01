FEATURE main.lua/Impl
loadMaterials = function(self, definition)
    print("TODO", "loadMaterials()")
    self:__loadShaderResources(definition)
    self:__createMaterials(definition)
    --self:__createMaterialCopies(definition)
end,

__createMaterials = function(self, definition)
    -- Original materials.
    local names = render.materialsDefinitionToMaterialNames(definition, true)
    for _, materialName in pairs(names)
    do
        -- Create material
        local material = self.__materialPool:createMaterial(materialName)

        local parameters = definition[materialName]

        -- Set shaders.
        local shaders = parameters["shaders"]
        if (shaders)
        then
            local group = shaders[1]
            local vertex = shaders[2]
            local fragment = shaders[3]
            local vertShader = resource.createResource(group, vertex)
            local fragShader = resource.createResource(group, fragment)
            material:setShaders(vertShader, fragShader)
        end

        -- Set uniforms.
        local uniforms = parameters["uniforms"]
        if (uniforms)
        then
            for uniformName, uniform in pairs(uniforms)
            do
                material:setUniform(uniformName, uniform)
            end
        end
    end
end,

__loadShaderResources = function(self, definition)
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
end,
