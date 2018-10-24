FEATURE main.h/Setup
this->setup_application_materialPool_material_setShaders();

FEATURE main.h/Impl
private:
    void setup_application_materialPool_material_setShaders()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.materialPool.material.setShaders"
            },
            this->process_application_materialPool_material_setShaders
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_materialPool_material_setShaders)
    {
        // Set.
        if (!values.empty())
        {
            // Make sure there are 5 components.
            if (values.size() != 5)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 5",
                    key.c_str()
                );
                return { };
            }

            auto materialName = values[0];
            auto vertexShaderGroup = values[1];
            auto vertexShaderName = values[2];
            auto fragmentShaderGroup = values[3];
            auto fragmentShaderName = values[4];

            auto material = this->app->materialPool->material(materialName);
            auto vertexShader =
                this->app->resourcePool->resource(
                    vertexShaderGroup,
                    vertexShaderName
                );
            auto fragmentShader =
                this->app->resourcePool->resource(
                    fragmentShaderGroup,
                    fragmentShaderName
                );

            // Make sure material and shaders exist.
            if (
                !material ||
                !vertexShader ||
                !fragmentShader
            ) {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set vertex shader '%s/%s' and fragment "
                    "shader '%s/%s' for material '%s' "
                    "because material and/or shader(s) do(es) not exist",
                    vertexShaderGroup.c_str(),
                    vertexShaderName.c_str(),
                    fragmentShaderGroup.c_str(),
                    fragmentShaderName.c_str(),
                    materialName.c_str()
                );
                return { };
            }

            auto prog =
                render::createShaderProgram(
                    resource::string(*vertexShader),
                    resource::string(*fragmentShader)
                );
            material->setAttribute(prog);
        }

        return { };
    }
