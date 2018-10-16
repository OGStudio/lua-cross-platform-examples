FEATURE main.lua/Impl
do
    local mouse = main.application.mouse
    -- Subscribe to mouse button presses.
    mouse.pressedButtonsChanged:addCallback(
        function()
            print("mouse pressed")
        end
    )
end
