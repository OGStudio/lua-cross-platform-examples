FEATURE main.h/Setup
this->setup_application_nodePool_node_setMask();

FEATURE main.h/Impl
private:
    void setup_application_nodePool_node_setMask()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.nodePool.node.setMask"
            },
            this->process_application_nodePool_node_setMask
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_setMask)
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

        auto name = values[0];
        auto node = this->app->nodePool->node(name);

        // Make sure node exists.
        if (!node)
        {
            MAIN_EXAMPLE_LOG(
                "ERROR Could not set mask for node named '%s' because "
                "it does not exist",
                name.c_str()
            );
            return { };
        }

        // Set mask.
        int mask = atof(values[1].c_str());
        node->setNodeMask(node->getNodeMask() & ~mask);

        return { };
    }
