FEATURE main.lua/Start
-- NOTE This is only a wrapper for a resource at C++ side.
-- NOTE This does NOT create anything at C++ side.
function resource.createResource(group, name)
    local instance = {
        __group = group,
        __name = name,

FEATURE main.lua/End
    }
    return instance
end
