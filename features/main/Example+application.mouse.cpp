FEATURE main.h/Setup
this->setupApplicationMouse();

FEATURE main.h/TearDown
this->tearApplicationMouseDown();

FEATURE main.h/Impl
private:
    const std::string applicationMousePressedButtonsKey =
        "application.mouse.pressedButtons";
    const std::string applicationMousePositionKey =
        "application.mouse.position";
    const std::string applicationMouseCallbackName =
        "ApplicationMouseTransmitter";

    void setupApplicationMouse()
    {
        // Transmit pressed buttons.
        this->app->mouse->pressedButtonsChanged.addCallback(
            [=] {
                this->transmitApplicationMouseButtons();
            },
            this->applicationMouseCallbackName
        );
        // Transmit position.
        this->app->mouse->positionChanged.addCallback(
            [=] {
                this->transmitApplicationMousePosition();
            },
            this->applicationMouseCallbackName
        );
        // NOTE We don't provide getters because Lua side
        // NOTE should keep the state itself.
        // NOTE Also, we don't provide setters because C++ side
        // NOTE has no such notion.
    }
    void tearApplicationMouseDown()
    {
        this->app->mouse->pressedButtonsChanged.removeCallback(
            this->applicationMouseCallbackName
        );
        this->app->mouse->positionChanged.removeCallback(
            this->applicationMouseCallbackName
        );
    }
    void transmitApplicationMouseButtons()
    {
        // Convert buttons to string representation.
        auto buttons = this->app->mouse->pressedButtons;
        std::vector<std::string> strbuttons;
        for (auto button : buttons)
        {
            strbuttons.push_back(mouseButtonToString(button));
        }
        // Transmit.
        this->environment->call(
            this->applicationMousePressedButtonsKey,
            strbuttons
        );
    }
    void transmitApplicationMousePosition()
    {
        // Convert position to string representation.
        auto position = this->app->mouse->position;
        std::vector<std::string> strposition = {
            format::printfString("%f", position.x()),
            format::printfString("%f", position.y()),
        };
        // Transmit.
        this->environment->call(
            this->applicationMousePositionKey,
            strposition
        );
    }
