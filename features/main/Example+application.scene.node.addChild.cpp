FEATURE main.h/Setup
this->setup_application_scene_node_addChild();

FEATURE main.h/TearDown
this->tearDown_application_scene_node_addChild();

FEATURE main.h/Impl
private:
    script::EnvironmentClient *client_application_scene_node_addChild;
    const std::string key_application_scene_node_addChild =
        "application.scene.node.addChild";

    void setup_application_scene_node_addChild()
    {
        this->client_application_scene_node_addChild =
            new script::EnvironmentClient;
        this->environment->addClient(
            this->client_application_scene_node_addChild
        );

        this->client_application_scene_node_addChild->respondsToKey =
            SCRIPT_ENVIRONMENT_CLIENT_RESPONDS_TO_KEY(
                return key == this->key_application_scene_node_addChild;
            );
        this->client_application_scene_node_addChild->call =
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                return
                    this->process_application_scene_node_addChild(key, values);
            );
    }
    void tearDown_application_scene_node_addChild()
    {
        delete this->client_application_scene_node_addChild;
    }
    script::EnvironmentClient::Values process_application_scene_node_addChild(
        const std::string &key,
        const script::EnvironmentClient::Values &values
    ) {
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

            auto scene = this->app->scene;
            auto parentName = values[0];
            auto childName = values[1];
            auto parent = scene->node(parentName);
            auto child = scene->node(childName);

            // Make sure parent and child exist.
            if (!parent || !child)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not add '%s' child node to '%s' parent node "
                    "because of the nodes does not exist",
                    childName.c_str(),
                    parentName.c_str()
                );
                return { };
            }

            parent->addChild(child);
        }

        return { };
    }
