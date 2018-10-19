FEATURE main.lua/Impl
main.application.parameters = {}
-- Transfer parameters from C++ to Lua.
do
    -- NOTE params = [key1, value1, key2, value2, ...].
    local params = ENV:call("application.parameters", {})
    local count = #params / 2
    for i = 1, count
    do
        local id = i * 2 - 1
        local key = params[id]
        local value = params[id + 1]
        main.application.parameters[key] = value
    end
end
