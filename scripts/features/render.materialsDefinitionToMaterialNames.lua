FEATURE main.lua/Impl
-- Extract material names: either original ones, or copies.
function render.materialsDefinitionToMaterialNames(definition, original)
    local names = {}

    -- Find materials with or without `copyOf` parameter.
    for name, parameters in pairs(definition)
    do
        local isOriginal = (parameters["copyOf"] == nil)
        if (isOriginal == original)
        then
            table.insert(names, name)
        end
    end

    return names
end
