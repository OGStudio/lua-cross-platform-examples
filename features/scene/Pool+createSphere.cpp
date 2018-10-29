FEATURE scene.h/Impl
public:
    osg::MatrixTransform *createSphere(
        const std::string &name,
        float radius
    ) {
        auto sphere = scene::createSphere(radius);
        sphere->setName(name);
        this->nodes[name] = sphere;
        return sphere;
    }
