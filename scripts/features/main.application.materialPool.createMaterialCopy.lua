FEATURE main.lua/Impl
main.application.materialPool.createMaterialCopy = function(self, name, reference)
    local key = "application.materialPool.createMaterialCopy"
    local result = ENV:call(key, {name, reference})
    -- Return nothing if copying failed.
    if (not result[1]) then
        return nil
    end
    -- Return material wrapper if copying succeeded.
    return render.createMaterial(name)
end
