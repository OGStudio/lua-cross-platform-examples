FEATURE main.h/Setup
this->setup_application_camera_clearColor();

FEATURE main.h/TearDown
this->tearDown_application_camera_clearColor();

FEATURE main.h/Impl
private:
    script::EnvironmentClient *client_application_camera_clearColor;
    void setup_application_camera_clearColor()
    {
        auto client = new script::EnvironmentClient;
        this->environment->addClient(
            client,
            {
                "application.camera.clearColor"
            }
        );
        client->call =
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                return this->process_application_camera_clearColor(key, values);
            );
        this->client_application_camera_clearColor = client;
    }
    void tearDown_application_camera_clearColor()
    {
        delete this->client_application_camera_clearColor;
    }
    std::vector<std::string> process_application_camera_clearColor(
        const std::string &key,
        const std::vector<std::string> &values
    ) {
        auto camera = this->app->camera();
        // Set.
        if (!values.empty())
        {
            // Make sure there are three components.
            if (values.size() != 3)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 3"
                );
                return { };
            }

            // Apply color.
            auto color = camera->getClearColor();
            color.r() = atof(values[0].c_str());
            color.g() = atof(values[1].c_str());
            color.b() = atof(values[2].c_str());
            camera->setClearColor(color);
        }

        // Return current color for Get and after Set.
        auto color = camera->getClearColor();
        return {
            format::printfString("%f", color.r()),
            format::printfString("%f", color.g()),
            format::printfString("%f", color.b()),
        };
    }
