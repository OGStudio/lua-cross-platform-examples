FEATURE main.lua/Impl
main.application.materialPool.createMaterial = function(self, name)
    local key = "application.materialPool.createMaterial"
    ENV:call(key, {name})
    return render.createMaterial(name)
end
