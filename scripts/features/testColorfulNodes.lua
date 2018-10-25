FEATURE main.lua/Impl
do
    -- Enable verbose Environment logging.
    --ENV:setVerbose(true)

    -- Make sure data directory has been specified.
    local dataDir = main.application.parameters["data"]
    if (dataDir == nil)
    then
        print(
            "ERROR",
            "You must specify data directory with `--data=/path/to/data`"
        )
        return
    end

    local nodePool = main.application.nodePool

    -- Create sphere node.
    local name = "sphere"
    local radius = 1
    local sphere = nodePool:createSphere(name, radius)
    local root = nodePool:node("root")
    root:addChild(sphere)

    local resourcePool = main.application.resourcePool
    print("Loading resources...")

    -- Specify resource locations in the lookup order.
    resourcePool:setLocations({
        dataDir
    })
    -- Load resources.
    resourcePool:loadResource(
        "shaders",
        "plain.vert"
    )
    resourcePool:loadResource(
        "shaders",
        "plain.frag"
    )

    print("Finished loading resources")

    -- Make sure all resources have been loaded successfully.
    local shaderVert = resourcePool:resource("shaders", "plain.vert")
    local shaderFrag = resourcePool:resource("shaders", "plain.frag")
    if (
        (shaderVert == nil) or
        (shaderFrag == nil)
    ) then
        print("ERROR", "Could not load one or more shaders")
        return
    end

    local materialPool = main.application.materialPool

    -- Create material to paint the whole scene.
    local material = materialPool:createMaterial("plain")
    material:setShaders(shaderVert, shaderFrag)
    root:setMaterial(material)

    -- Set material color.
    material:setUniform("color", {0.5, 0.5, 0.5})
end
