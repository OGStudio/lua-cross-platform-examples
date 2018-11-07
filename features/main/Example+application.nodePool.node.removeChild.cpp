FEATURE main.h/Setup
this->setup_application_nodePool_node_removeChild();

FEATURE main.h/Impl
private:
    void setup_application_nodePool_node_removeChild()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.nodePool.node.removeChild"
            },
            this->process_application_nodePool_node_removeChild
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_removeChild)
    {
        // Set.
        if (!values.empty())
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

            auto pool = this->app->nodePool;
            auto parentName = values[0];
            auto childName = values[1];
            auto parent = pool->node(parentName);
            auto child = pool->node(childName);

            // Make sure parent and child exist.
            if (!parent || !child)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not remove '%s' child node from '%s' parent node "
                    "because of the node(s) do(es) not exist",
                    childName.c_str(),
                    parentName.c_str()
                );
                return { };
            }

            parent->removeChild(child);
        }

        return { };
    }
