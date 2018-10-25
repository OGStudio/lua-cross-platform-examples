FEATURE main.h/Setup
this->setup_application_nodePool_node_setMaterial();

FEATURE main.h/Impl
private:
    void setup_application_nodePool_node_setMaterial()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.nodePool.node.setMaterial"
            },
            this->process_application_nodePool_node_setMaterial
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_setMaterial)
    {
        // Set.
        if (!values.empty())
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

            std::string materialName = "(nil)";
            osg::StateSet *material = 0;
            if (values.size() == 2)
            {
                materialName = values[1];
                material = this->app->materialPool->material(materialName);
            }

            // Make sure node exists.
            if (!node)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set material '%s' for node '%s' "
                    "because node do(es) not exist",
                    materialName.c_str(),
                    nodeName.c_str()
                );
                return { };
            }

            node->setStateSet(material);
        }

        return { };
    }
