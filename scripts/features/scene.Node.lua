FEATURE main.lua/Methods
-- NOTE This is only a wrapper for a valid node at C++ side.
-- NOTE This does NOT create anything at C++ side.
function scene.createNode(name)
    local instance = {
        __name = name,

FEATURE main.lua/Properties
    }

    -- Set metatable to have properties easily.
    local propertiesMT = core.createPropertiesMT()
    setmetatable(instance, propertiesMT)

FEATURE main.lua/End
    return instance
end
