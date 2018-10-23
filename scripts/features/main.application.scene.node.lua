FEATURE main.lua/Impl
function main.application.scene.node(self, name)
    local key = "application.scene.node.exists"
    -- Find out if node exists in C++.
    local result = ENV:call(key, {name})
    -- Return nothing if node does not exist.
    if (not result[1]) then
        return nil
    end
    -- Return Lua node representation if node exists in C++.
    return scene.createNode(name)
end
