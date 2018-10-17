FEATURE main.h/Setup
this->setup_application_scene_createSphere();

FEATURE main.h/TearDown
this->tearDown_application_scene_createSphere();

FEATURE main.h/Impl
private:
    script::EnvironmentClient *client_application_scene_createSphere;
    const std::string key_application_scene_createSphere =
        "application.scene.createSphere";

    void setup_application_scene_createSphere()
    {
        this->client_application_scene_createSphere = new script::EnvironmentClient;
        this->environment->addClient(this->client_application_scene_createSphere);

        this->client_application_scene_createSphere->respondsToKey =
            SCRIPT_ENVIRONMENT_CLIENT_RESPONDS_TO_KEY(
                return key == this->key_application_scene_createSphere;
            );
        this->client_application_scene_createSphere->call =
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                return this->process_application_scene_createSphere(key, values);
            );
    }
    void tearDown_application_scene_createSphere()
    {
        delete this->client_application_scene_createSphere;
    }
    script::EnvironmentClient::Values process_application_scene_createSphere(
        const std::string &key,
        const script::EnvironmentClient::Values &values
    ) {
        auto scene = this->app->scene;
        // Set.
        if (!values.empty())
        {
            // Make sure there are two components.
            if (values.size() != 2)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 2"
                );
                return { };
            }

            // Create sphere.
            auto name = values[0];
            auto radius = atof(values[1].c_str());
            scene->createSphere(name, radius);
        }

        return { };
    }
