FEATURE main.h/Setup
this->setup_application_nodePool_node_position();

FEATURE main.h/Impl
private:
    void setup_application_nodePool_node_position()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.nodePool.node.position"
            },
            this->process_application_nodePool_node_position
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_position)
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
                "ERROR Could not get or set position for node '%s' "
                "because it does not exist",
                nodeName.c_str()
            );
            return { };
        }

        // Set.
        if (values.size() == 4)
        {
            osg::Vec3 position(
                atof(values[1].c_str()),
                atof(values[2].c_str()),
                atof(values[3].c_str())
            );
            scene::setSimplePosition(node, position);
        }

        // Get.
        auto position = scene::simplePosition(node);
        return {
            format::printfString("%f", position.x()),
            format::printfString("%f", position.y()),
            format::printfString("%f", position.z()),
        };
    }
