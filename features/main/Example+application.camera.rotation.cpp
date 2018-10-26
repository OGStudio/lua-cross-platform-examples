FEATURE main.h/Setup
this->setup_application_camera_rotation();

FEATURE main.h/Impl
private:
    void setup_application_camera_rotation()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.camera.rotation"
            },
            this->process_application_camera_rotation
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_camera_rotation)
    {
        auto manipulator = this->app->cameraManipulator();
        osg::Vec3d pos;
        osg::Quat q;
        manipulator->getTransformation(pos, q);

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

            // Apply rotation.
            osg::Vec3d rot = {
                atof(values[0].c_str()),
                atof(values[1].c_str()),
                atof(values[2].c_str()),
            };
            q = scene::degreesToQuaternion(rot);
            manipulator->setTransformation(pos, q);
        }

        // Return current position for Get and after Set.
        manipulator->getTransformation(pos, q);
        auto rot = scene::quaternionToDegrees(q);
        return {
            format::printfString("%f", rot.x()),
            format::printfString("%f", rot.y()),
            format::printfString("%f", rot.z()),
        };
    }
