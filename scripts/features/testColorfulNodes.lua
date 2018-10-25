FEATURE main.lua/Impl
do
    -- Enable verbose Environment logging.
    ENV:setVerbose(true)

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

    -- Define distinct setup stages.
    function createSphereNode(nodePool)
        local name = "sphere"
        local radius = 1
        local sphere = nodePool:createSphere(name, radius)
        local root = nodePool:node("root")
        root:addChild(sphere)
    end
    function loadResources(resourcePool, dataDir)
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
    end
    function finishSetup(resourcePool, materialPool, nodePool)
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

        -- Create material to paint the whole scene.
        local material = materialPool:createMaterial("plain")
        material:setShaders(shaderVert, shaderFrag)
        local root = nodePool:node("root")
        root:setMaterial(material)
    end

    local nodePool = main.application.nodePool
    createSphereNode(nodePool)

    local resourcePool = main.application.resourcePool
    print("Loading resources...")
    loadResources(resourcePool, dataDir)
    print("Finished loading resources")

    local materialPool = main.application.materialPool
    finishSetup(resourcePool, materialPool, nodePool)
end
