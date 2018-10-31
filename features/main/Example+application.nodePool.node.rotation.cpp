FEATURE main.h/Setup
this->setup_application_nodePool_node_rotation();

FEATURE main.h/Impl
private:
    void setup_application_nodePool_node_rotation()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.nodePool.node.rotation"
            },
            this->process_application_nodePool_node_rotation
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_rotation)
    {
        // Make sure there is at least one component.
        if (values.size() < 1)
        {
            MAIN_EXAMPLE_LOG(
                "ERROR Could not set value for key '%s' "
                "because values' count is less than 1",
                key.c_str()
            );
            return { };
        }

        auto nodeName = values[0];
        auto node = this->app->nodePool->node(nodeName);

        // Make sure node exists.
        if (!node)
        {
            MAIN_EXAMPLE_LOG(
                "ERROR Could not get or set rotation for node '%s' "
                "because it does not exist",
                nodeName.c_str()
            );
            return { };
        }

        // Set.
        if (values.size() == 4)
        {
            osg::Vec3 rotation(
                atof(values[1].c_str()),
                atof(values[2].c_str()),
                atof(values[3].c_str())
            );
            scene::setSimpleRotation(node, rotation);
        }

        // Get.
        auto rotation = scene::simpleRotation(node);
        return {
            format::printfString("%f", rotation.x()),
            format::printfString("%f", rotation.y()),
            format::printfString("%f", rotation.z()),
        };
    }
