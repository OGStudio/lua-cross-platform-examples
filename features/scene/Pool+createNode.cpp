FEATURE scene.h/Impl
public:
    osg::MatrixTransform *createNode(const std::string &name)
    {
        auto node = new osg::MatrixTransform;
        this->nodes[name] = node;
        return node;
    }
