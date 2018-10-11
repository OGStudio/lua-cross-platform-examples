FEATURE main.h/Setup
this->setupApplicationCameraClearColor();

FEATURE main.h/TearDown
this->tearApplicationCameraClearColorDown();

FEATURE main.h/Impl
private:
    script::EnvironmentClient *applicationCameraClearColorClient;
    const std::string applicationCameraClearColorKey =
        "application.camera.clearColor";

    void setupApplicationCameraClearColor()
    {
        this->applicationCameraClearColorClient = new script::EnvironmentClient;
        this->environment->addClient(this->applicationCameraClearColorClient);

        this->applicationCameraClearColorClient->respondsToKey =
            SCRIPT_ENVIRONMENT_CLIENT_RESPONDS_TO_KEY(
                return key == this->applicationCameraClearColorKey;
            );
        this->applicationCameraClearColorClient->call =
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                return this->processApplicationCameraClearColor(key, values);
            );
    }
    void tearApplicationCameraClearColorDown()
    {
        delete this->applicationCameraClearColorClient;
    }
    script::EnvironmentClient::Values processApplicationCameraClearColor(
        const std::string &key,
        const script::EnvironmentClient::Values &values
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
                script::EnvironmentClient::Values empty;
                return empty;
            }

            // Apply color.
            auto color = camera->getClearColor();
            color.r() = atof(values[0].c_str());
            color.g() = atof(values[1].c_str());
            color.b() = atof(values[2].c_str());
            camera->setClearColor(color);
        }

        // Return current color for Get and after successful Set.
        auto color = camera->getClearColor();
        return {
            format::printfString("%f", color.r()),
            format::printfString("%f", color.g()),
            format::printfString("%f", color.b()),
        };
    }
