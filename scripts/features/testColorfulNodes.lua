FEATURE main.lua/Impl
do
    local name = "sphere"
    local radius = 1
    local sphere = main.application.scene:createSphere(name, radius)
    local root = main.application.scene:node("root")
    root:addChild(sphere)

    local mouse = main.application.mouse
    -- Subscribe to mouse button presses.
    mouse.pressedButtonsChanged:addCallback(
        function()
            print("mouse pressed")
        end
    )
end
