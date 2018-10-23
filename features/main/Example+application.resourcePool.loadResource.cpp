FEATURE main.h/Setup
this->setup_application_resourcePool_loadResource();

FEATURE main.h/Impl
private:
    void setup_application_resourcePool_loadResource()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.resourcePool.loadResource"
            },
            this->process_application_resourcePool_loadResource
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_resourcePool_loadResource)
    {
        auto pool = this->app->resourcePool;
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

            auto group = values[0];
            auto name = values[1];
            pool->loadResource(group, name);
        }

        return { };
    }
