FEATURE main.h/Setup
this->setup_application_materialPool_material_setUniform();

FEATURE main.h/Impl
private:
    void setup_application_materialPool_material_setUniform()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.materialPool.material.setUniform"
            },
            this->process_application_materialPool_material_setUniform
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_materialPool_material_setUniform)
    {
        // Set.
        if (!values.empty())
        {
            // Make sure there are at least three components.
            if (values.size() < 3)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is less than 3",
                    key.c_str()
                );
                return { };
            }

            auto materialName = values[0];
            auto uniformName = values[1];

            // We only support vec3 values.
            // TODO Support other values, too.
            if (values.size() != 5)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Cannot set value for uniform '%s' of material '%s' "
                    "because we only support vec3 values for now",
                    uniformName.c_str(),
                    materialName.c_str()
                );
                return { };
            }

            auto material = this->app->materialPool->material(materialName);

            // Make sure material exists.
            if (!material)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not uniform '%s' for material '%s' "
                    "because material does not exist",
                    uniformName.c_str(),
                    materialName.c_str()
                );
                return { };
            }

            osg::Uniform *uniform =
                material->getOrCreateUniform(
                    uniformName,
                    osg::Uniform::FLOAT_VEC3
                );
            osg::Vec3 vector(
                atof(values[2].c_str()),
                atof(values[3].c_str()),
                atof(values[4].c_str())
            );
            uniform->set(vector);
        }

        return { };
    }
