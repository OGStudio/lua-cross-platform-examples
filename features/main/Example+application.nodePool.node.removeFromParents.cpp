FEATURE main.h/Setup
this->setup_application_nodePool_node_removeFromParents();

FEATURE main.h/Impl
private:
    void setup_application_nodePool_node_removeFromParents()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.nodePool.node.removeFromParents"
            },
            this->process_application_nodePool_node_removeFromParents
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_removeFromParents)
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

            auto nodeName = values[0];
            auto node = this->app->nodePool->node(nodeName);

            // Make sure node exists.
            if (!node)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not remove parents of '%s' node "
                    "because it does not exist",
                    nodeName.c_str()
                );
                return { };
            }

            // Remove from parents.
            auto parents = node->getParents();
            for (auto parent : parents)
            {
                parent->removeChild(node);
            }
        }

        return { };
    }
