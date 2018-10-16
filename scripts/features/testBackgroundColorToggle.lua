FEATURE main.lua/Impl
do
    -- Define toggling function.
    local function toggleCameraColor(camera, color1, color2)
        -- Get current camera color.
        local color = camera.clearColor
        -- Toggle color.
        if 
            (color[1] == color1[1]) and
            (color[2] == color1[2]) and
            (color[3] == color1[3])
        then
            color = color2
        else
            color = color1
        end
        -- Apply new color.
        camera.clearColor = color
    end

    -- Define shortcuts to globals.
    local camera = main.application.camera
    local mouse = main.application.mouse
    -- Define colors to toggle between.
    local colorSrc = camera.clearColor
    local colorDst = {0.5, 0.5, 0.5}

    -- Subscribe to mouse button presses.
    mouse.pressedButtonsChanged:addCallback(
        function()
            -- Detect click.
            if (#mouse.pressedButtons > 0)
            then
                toggleCameraColor(camera, colorSrc, colorDst)
            end
        end
    )

    print("Message to user: click to change background color")
end
