FEATURE main.h/Setup
this->setup_application_scene_createSphere();

FEATURE main.h/Impl
private:
    void setup_application_scene_createSphere()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.scene.createSphere"
            },
            this->process_application_scene_createSphere
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_scene_createSphere)
    {
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
            auto scene = this->app->scene;
            auto name = values[0];
            auto radius = atof(values[1].c_str());
            scene->createSphere(name, radius);
        }

        return { };
    }
