FEATURE main.h/Setup
this->setup_application_resourcePool_locations();

FEATURE main.h/Impl
private:
    void setup_application_resourcePool_locations()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.resourcePool.locations"
            },
            this->process_application_resourcePool_locations
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_resourcePool_locations)
    {
        auto pool = this->app->resourcePool;
        // Set.
        if (!values.empty())
        {
            pool->locations = values;
        }

        // Return current locations for both Get and Set.
        return pool->locations;
    }
