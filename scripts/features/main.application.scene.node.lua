FEATURE main.lua/Impl
function main.application.scene.node(self, name)
    local key = "application.scene.node.exists"
    -- Find out if node exists in C++.
    local result = ENV:call(key, {name})
    -- Return nothing if node does not exist.
    if (result.length == 0) then
        return nil
    end
    -- Return Lua node representation inf node exists in C++.
    return scene.createNode(name)
end
