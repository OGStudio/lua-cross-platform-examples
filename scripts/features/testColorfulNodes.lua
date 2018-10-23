FEATURE main.lua/Impl
do
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
    function areResourcesValid(resourcePool)
        -- Make sure all resources have been loaded successfully.
        local shaderVert = resourcePool:resource("shaders", "plain.vert")
        local shaderFrag = resourcePool:resource("shaders", "plain.frag")
        if (
            (shaderVert == nil) or
            (shaderFrag == nil)
        ) then
            print("ERROR", "Could not load one or more shaders")
            return false
        end

        return true
    end
    function finishSetup(resourcePool)
        print("TODO Paint the node with single-color shader")
        -- TODO Paint the node with single-color shader.

    end

    local nodePool = main.application.nodePool
    createSphereNode(nodePool)

    local resourcePool = main.application.resourcePool
    print("Loading resources...")
    loadResources(resourcePool, dataDir)

    print("Finished loading resources")
    if (areResourcesValid(resourcePool))
    then
        finishSetup(resourcePool)
    end
end
