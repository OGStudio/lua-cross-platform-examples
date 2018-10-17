FEATURE main.h/Setup
this->setup_application_scene_node_exists();

FEATURE main.h/TearDown
this->tearDown_application_scene_node_exists();

FEATURE main.h/Impl
private:
    script::EnvironmentClient *client_application_scene_node_exists;
    const std::string key_application_scene_node_exists =
        "application.scene.node.exists";

    void setup_application_scene_node_exists()
    {
        this->client_application_scene_node_exists =
            new script::EnvironmentClient;
        this->environment->addClient(
            this->client_application_scene_node_exists
        );

        this->client_application_scene_node_exists->respondsToKey =
            SCRIPT_ENVIRONMENT_CLIENT_RESPONDS_TO_KEY(
                return key == this->key_application_scene_node_exists;
            );
        this->client_application_scene_node_exists->call =
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                return
                    this->process_application_scene_node_exists(key, values);
            );
    }
    void tearDown_application_scene_node_exists()
    {
        delete this->client_application_scene_node_exists;
    }
    script::EnvironmentClient::Values process_application_scene_node_exists(
        const std::string &key,
        const script::EnvironmentClient::Values &values
    ) {
        // Set.
        if (!values.empty())
        {
            // Make sure there is one component.
            if (values.size() != 1)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 1"
                );
                return { };
            }

            auto scene = this->app->scene;
            auto name = values[0];
            auto node = scene->node(name);
            if (node != 0)
            {
                return { "true" };
            }
        }

        return { };
    }
