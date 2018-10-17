FEATURE main.lua/Start
-- NOTE This is only a wrapper for valid node at C++ side.
-- NOTE This does NOT create anything at C++ side.
function scene.createNode(name)
    local instance = {
        __name = name,

FEATURE main.lua/End
    }
    return instance
end
