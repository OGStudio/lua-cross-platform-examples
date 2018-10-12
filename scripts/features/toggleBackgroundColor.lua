FEATURE main.lua/Impl
local function toggleBackgroundColor(camera)
    print("TODO Toggle background color")

    local color = camera.clearColor
    print("Previous background color:", color[1], color[2], color[3])

    -- Set new color.
    camera.clearColor = {0.5, 0.5, 0.5}

    color = camera.clearColor
    print("Current background color:", color[1], color[2], color[3])
end

toggleBackgroundColor(application.camera)
