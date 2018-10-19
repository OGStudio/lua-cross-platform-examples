FEATURE main.lua/Impl
do
    -- TODO Update to use nodePool
    local scene = main.application.scene
    -- Create sphere node.
    local name = "sphere"
    local radius = 1
    local sphere = scene:createSphere(name, radius)
    local root = scene:node("root")
    root:addChild(sphere)
    -- Set data directory.
    local dataDir = main.application.parameters["data"]
    -- TODO local resourcePool = main.application.resourcePool
    if (dataDir)
    then
        print("Data dir:", dataDir)
        -- TODO resourcePool.setDataDir(dataDir)
    end
    -- Paint the node with single-color shader.
    --[[
    --]]

    local mouse = main.application.mouse
    -- Subscribe to mouse button presses.
    mouse.pressedButtonsChanged:addCallback(
        function()
            print("mouse pressed")
        end
    )
end
