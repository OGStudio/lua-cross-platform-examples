FEATURE scene.h/Setup
this->setupRoot();

FEATURE scene.h/Impl
private:
    void setupRoot()
    {
        auto root = new osg::MatrixTransform;
        this->nodes["root"] = root;
    }
