FEATURE main.h/Setup
this->setup_application_resourcePool_resource_exists();

FEATURE main.h/Impl
private:
    void setup_application_resourcePool_resource_exists()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.resourcePool.resource.exists"
            },
            this->process_application_resourcePool_resource_exists
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_resourcePool_resource_exists)
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

            auto pool = this->app->resourcePool;
            auto group = values[0];
            auto name = values[1];
            auto res = pool->resource(group, name);
            if (res != 0)
            {
                return { "true" };
            }
        }

        return { };
    }
