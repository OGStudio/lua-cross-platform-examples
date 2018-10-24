FEATURE main.lua/Start
-- NOTE This is only a wrapper for a valid node at C++ side.
-- NOTE This does NOT create anything at C++ side.
function render.createMaterial(name)
    local instance = {
        __name = name,

FEATURE main.lua/End
    }
    return instance
end
