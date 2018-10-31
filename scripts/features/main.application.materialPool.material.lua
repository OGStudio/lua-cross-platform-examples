FEATURE main.lua/Impl
function main.application.materialPool.material(self, name)
    local key = "application.materialPool.material.exists"
    -- Find out if material exists in C++.
    local result = ENV:call(key, {name})
    -- Return nothing if material does not exist.
    if (not result[1]) then
        return nil
    end
    -- Return Lua material representation if material exists in C++.
    return render.createMaterial(name)
end
