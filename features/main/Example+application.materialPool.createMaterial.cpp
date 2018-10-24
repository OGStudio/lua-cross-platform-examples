FEATURE main.h/Setup
this->setup_application_materialPool_createMaterial();

FEATURE main.h/Impl
private:
    void setup_application_materialPool_createMaterial()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.materialPool.createMaterial"
            },
            this->process_application_materialPool_createMaterial
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_materialPool_createMaterial)
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

            // Create material.
            auto pool = this->app->materialPool;
            auto name = values[0];
            pool->createMaterial(name);
        }

        return { };
    }
