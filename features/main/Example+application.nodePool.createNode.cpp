FEATURE main.h/Setup
this->setup_application_nodePool_createNode();

FEATURE main.h/Impl
private:
    void setup_application_nodePool_createNode()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.nodePool.createNode"
            },
            this->process_application_nodePool_createNode
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_createNode)
    {
        // Set.
        if (!values.empty())
        {
            // Make sure there is one component.
            if (values.size() != 1)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 1"
                );
                return { };
            }

            // Create node.
            auto pool = this->app->nodePool;
            auto name = values[0];
            pool->createNode(name);
        }

        return { };
    }
