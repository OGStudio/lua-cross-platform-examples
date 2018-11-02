FEATURE main.lua/Impl
loadMaterials = function(self, definition)
    self:__loadShaderResources(definition)
    self:__createMaterials(definition)
    self:__createMaterialCopies(definition)
end,

__createMaterials = function(self, definition)
    -- Original materials.
    local names = render.materialsDefinitionToMaterialNames(definition, true)
    for _, materialName in pairs(names)
    do
        -- Create material.
        local material = self.__materialPool:createMaterial(materialName)
        local parameters = definition[materialName]
        self:__setMaterialShaders(material, parameters)
        self:__setMaterialUniforms(material, parameters)
    end
end,

__createMaterialCopies = function(self, definition)
    -- Material copies.
    local names = render.materialsDefinitionToMaterialNames(definition, false)
    for _, materialName in pairs(names)
    do
        local parameters = definition[materialName]
        local referenceMaterialName = parameters["copyOf"] 

        -- Create material as a copy.
        local material =
            self.__materialPool:createMaterialCopy(
                materialName,
                referenceMaterialName
            )
        self:__setMaterialShaders(material, parameters)
        self:__setMaterialUniforms(material, parameters)
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

__setMaterialShaders = function(self, material, parameters)
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
end,

__setMaterialUniforms = function(self, material, parameters)
    local uniforms = parameters["uniforms"]
    if (uniforms)
    then
        for uniformName, uniform in pairs(uniforms)
        do
            material:setUniform(uniformName, uniform)
        end
    end
end,
