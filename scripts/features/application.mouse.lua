FEATURE main.lua/Impl
-- Create mouse.
application.mouse = {
    position = {},
    positionChanged = createReporter(),

    pressedButtons = {},
    pressedButtonsChanged = createReporter(),
}

-- Configure it.
do
    local mouse = application.mouse
    -- Create environment client.
    local client = EnvironmentClient.new()
    -- Define keys.
    local buttonsKey = "application.mouse.pressedButtons"
    local positionKey = "application.mouse.position"
    -- Define methods.
    client.respondsToKey = function(key)
        return
            (key == buttonsKey) or
            (key == positionKey)
    end
    client.call = function(key, values)
        if (key == buttonsKey)
        then
            mouse.pressedButtons = values
            mouse.pressedButtonsChanged:report()
        elseif (key == positionKey)
        then
            mouse.position = values
            mouse.positionChanged:report()
        end

        return {}
    end
    -- Register client.
    mouse.client = client
    ENV:addClient(mouse.client);
end
