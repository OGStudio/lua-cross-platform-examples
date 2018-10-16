FEATURE main.lua/Impl
do
    --[[
    local poolName = "sample"
    main.application.nodePools:createPool("sample")
    local pool = main.application.nodePools["sample"]
    local sphereName = "sphere"
    local radius = 1
    pool:createSphere(sphereName, radius)
    main.application:setScene(pool, sphereName)
    --]]

    local mouse = main.application.mouse
    -- Subscribe to mouse button presses.
    mouse.pressedButtonsChanged:addCallback(
        function()
            print("mouse pressed")
        end
    )
end
