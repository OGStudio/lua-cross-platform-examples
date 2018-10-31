FEATURE main.h/Setup
this->setup_application_materialPool_material_exists();

FEATURE main.h/Impl
private:
    void setup_application_materialPool_material_exists()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.materialPool.material.exists"
            },
            this->process_application_materialPool_material_exists
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_materialPool_material_exists)
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

            auto pool = this->app->materialPool;
            auto name = values[0];
            auto material = pool->material(name);
            if (material != 0)
            {
                return { "true" };
            }
        }

        return { };
    }
