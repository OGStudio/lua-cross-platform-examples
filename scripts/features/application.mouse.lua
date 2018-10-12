FEATURE main.lua/Impl
-- Create mouse.
application.mouse = {
    position = {},
    pressedButtons = {},
}

-- Configure it.
do
    local mouse = application.mouse
    -- Create and configure environment client.
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
            mouse.position = values
            print("accepted mouse position")
        elseif (key == positionKey)
        then
            mouse.pressedButtons = values
            print("accepted mouse pressed buttons")
        end

        return {}
    end

    -- Register client.
    application.mouse.client = client
    ENV:addClient(application.mouse.client);
end
