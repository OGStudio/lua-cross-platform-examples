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
    function createSphereNode(scene)
        local name = "sphere"
        local radius = 1
        local sphere = scene:createSphere(name, radius)
        local root = scene:node("root")
        root:addChild(sphere)
    end
    function loadResources(resourcePool, dataDir)
        resourcePool.setDataDir(dataDir)
        -- Load resources.
        resourcePool:loadResource(
            "shaders",
            "plain.vert"
        )
        resourcePool:loadResource(
            "shaders",
            "plain.frag"
        )
        -- TODO Specify list of sources to get resource from
        -- TODO Specify dir1, web1, dir2, web2, only then fail.
    end
    function areResourcesValid(resourcePool)
        -- Make sure all resources have been loaded successfully.
        local shaderVert = resourcePool:resource("shaders", "plain.vert")
        local shaderFrag = resourcePool:resource("shaders", "plain.frag")
        if (
            (shaderVert == nil) ||
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

    -- TODO Use nodePool
    local scene = main.application.scene
    createSphereNode(scene)

    local resourcePool = main.application.resourcePool
    print("Loading resources...")
    loadResources(resourcePool, dataDir)

    resourcePool.finishedLoading:addOneTimeCallback(
        function()
            print("Finished loading resources")
            if (areResourcesValid(resourcePool))
            then
                finishSetup(resourcePool)
            end
        end
    )
end
