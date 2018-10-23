FEATURE main.h/Setup
this->setup_application_nodePool_node_exists();

FEATURE main.h/Impl
private:
    void setup_application_nodePool_node_exists()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.nodePool.node.exists"
            },
            this->process_application_nodePool_node_exists
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_exists)
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

            auto pool = this->app->nodePool;
            auto name = values[0];
            auto node = pool->node(name);
            if (node != 0)
            {
                return { "true" };
            }
        }

        return { };
    }
