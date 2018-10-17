FEATURE main.lua/Impl
main.application.scene.createSphere = function(self, name, radius)
    local key = "application.scene.createSphere"
    ENV:call(key, {name, radius})
    return scene.createNode(name)
end
