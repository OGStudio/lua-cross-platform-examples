FEATURE main.lua/Start
-- NOTE This is only a wrapper for a valid node at C++ side.
-- NOTE This does NOT create anything at C++ side.
function main.createMaterialLoader(materialPool, resourcePool)
    local instance = {
        __materialPool = materialPool,
        __resourcePool = resourcePool,

FEATURE main.lua/End
    }

    return instance
end
