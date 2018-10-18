FEATURE main.lua/Impl
do
    local scene = main.application.scene
    -- Create sphere node.
    local name = "sphere"
    local radius = 1
    local sphere = scene:createSphere(name, radius)
    local root = scene:node("root")
    root:addChild(sphere)

    local mouse = main.application.mouse
    -- Subscribe to mouse button presses.
    mouse.pressedButtonsChanged:addCallback(
        function()
            print("mouse pressed")
        end
    )
end
