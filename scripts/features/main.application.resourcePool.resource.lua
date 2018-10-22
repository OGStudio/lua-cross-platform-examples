FEATURE main.lua/Impl
function main.application.resourcePool.resource(self, group, name)
    local key = "application.resourcePool.resource.exists"
    -- Find out if resource exists in C++.
    local result = ENV:call(key, {group, name})
    -- Return nothing if resource does not exist.
    if (result.length == 0) then
        return nil
    end
    -- Return Lua node representation if resource exists in C++.
    return resource.createResource(group, name)
end
