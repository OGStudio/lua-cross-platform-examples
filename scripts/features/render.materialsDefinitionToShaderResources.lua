FEATURE main.lua/Impl
-- Extract shader resources to load from materials' definition.
function render.materialsDefinitionToShaderResources(definition)
    local resources = {}
    -- Materials.
    for materialName, parameters in pairs(definition)
    do
        -- Parameters.
        for parameterName, parameter in pairs(parameters)
        do
            -- Shader resources.
            if (parameterName == "shaders")
            then
                local resource =
                    render.materialsDefinitionShadersResource(parameter)
                if (resource)
                then
                    table.insert(resources, resource)
                end
            end
        end
    end
    return resources
end

function render.materialsDefinitionShadersResource(definition)
    -- Make sure there are three components.
    if (#definition ~= 3)
    then
        print(
            "ERROR",
            "Cannot parse shaders in materials' definition " ..
            "because the number of components is not 3"
        )
        return nil
    end

    return definition
end
