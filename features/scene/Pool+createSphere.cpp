FEATURE scene.h/Impl
public:
    osg::MatrixTransform *createSphere(
        const std::string &name,
        float radius
    ) {
        auto sphere = scene::createSphere(radius);
        this->nodes[name] = sphere;
        return sphere;
    }
