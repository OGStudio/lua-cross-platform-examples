FEATURE render.h/Impl
public:
    osg::StateSet *createMaterialCopy(
        const std::string &name,
        const std::string &referenceName
    ) {
        auto reference = this->material(referenceName);
        // Make sure reference material exists.
        if (!reference)
        {
            RENDER_MATERIAL_POOL_LOG(
                "ERROR Could not create a copy of material '%s' "
                "because it does not exist",
                referenceName.c_str()
            );
            return 0;
        }

        // Create material copy.
        auto material =
            new osg::StateSet(*reference, osg::CopyOp::DEEP_COPY_ALL);
        this->materials[name] = material;
        return material;
    }
