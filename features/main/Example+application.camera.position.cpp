FEATURE main.h/Setup
this->setup_application_camera_position();

FEATURE main.h/Impl
private:
    void setup_application_camera_position()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.camera.position"
            },
            this->process_application_camera_position
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_camera_position)
    {
        auto manipulator = this->app->cameraManipulator();
        osg::Vec3d pos;
        osg::Quat q;

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

            // Apply position.
            pos = {
                atof(values[0].c_str()),
                atof(values[1].c_str()),
                atof(values[2].c_str()),
            };
            manipulator->setTransformation(pos, q);
        }

        // Return current position for Get and after Set.
        manipulator->getTransformation(pos, q);
        return {
            format::printfString("%f", pos.x()),
            format::printfString("%f", pos.y()),
            format::printfString("%f", pos.z()),
        };
    }
