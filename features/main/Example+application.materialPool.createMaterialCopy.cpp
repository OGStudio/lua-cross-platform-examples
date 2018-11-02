FEATURE main.h/Setup
this->setup_application_materialPool_createMaterialCopy();

FEATURE main.h/Impl
private:
    void setup_application_materialPool_createMaterialCopy()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.materialPool.createMaterialCopy"
            },
            this->process_application_materialPool_createMaterialCopy
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_materialPool_createMaterialCopy)
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

            // Create material copy.
            auto name = values[0];
            auto reference = values[1];
            auto material =
                this->app->materialPool->createMaterialCopy(name, reference);

            if (material)
            {
                return { "true" };
            }
        }

        return { };
    }
