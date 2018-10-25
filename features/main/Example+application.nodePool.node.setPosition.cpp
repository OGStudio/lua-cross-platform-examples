FEATURE main.h/Setup
this->setup_application_nodePool_node_setPosition();

FEATURE main.h/Impl
private:
    void setup_application_nodePool_node_setPosition()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.nodePool.node.setPosition"
            },
            this->process_application_nodePool_node_setPosition
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_setPosition)
    {
        // Set.
        if (!values.empty())
        {
            // Make sure there are 4 components.
            if (values.size() != 4)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 4",
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
                    "ERROR Could not set position for node '%s' "
                    "because node does not exist",
                    nodeName.c_str()
                );
                return { };
            }

            osg::Vec3 position(
                atof(values[1].c_str()),
                atof(values[2].c_str()),
                atof(values[3].c_str())
            );
            scene::setSimplePosition(node, position);
        }

        return { };
    }
