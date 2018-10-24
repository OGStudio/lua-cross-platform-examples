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
            // Make sure there are two components.
            if (values.size() != 2)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 2",
                    key.c_str()
                );
                return { };
            }

            auto nodeName = values[0];
            auto materialName = values[1];

            auto node = this->app->nodePool->node(nodeName);
            auto material = this->app->materialPool->material(materialName);

            // Make sure node and material exist.
            if (
                !node ||
                !material
            ) {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set material '%s' for node '%s' "
                    "because node and/or material do(es) not exist",
                    materialName.c_str(),
                    nodeName.c_str()
                );
                return { };
            }

            node->setStateSet(material);
        }

        return { };
    }
