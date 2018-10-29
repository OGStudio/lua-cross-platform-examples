FEATURE scene.h/Impl
public:
    osg::MatrixTransform *createNode(const std::string &name)
    {
        auto node = new osg::MatrixTransform;
        node->setName(name);
        this->nodes[name] = node;
        return node;
    }
