FEATURE main.h/Setup
this->setup_application_camera_nodeAtPosition();

FEATURE main.h/Impl
private:
    void setup_application_camera_nodeAtPosition()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.camera.nodeAtPosition"
            },
            this->process_application_camera_nodeAtPosition
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_camera_nodeAtPosition)
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

        osg::Vec2d position = {
            atof(values[0].c_str()),
            atof(values[1].c_str()),
        };
        int selectionMask = atoi(values[2].c_str());

        // Locate a node.
        auto node =
            scene::nodeAtPosition(
                position,
                this->app->camera(),
                selectionMask
            );

        // Return the name of the node if it exists.
        if (node)
        {
            return { node->getName() };
        }

        // Return nothing otherwise.
        return { };
    }
