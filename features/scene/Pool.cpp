FEATURE scene.h/Include
#include <osg/MatrixTransform>

FEATURE scene.h/Setup
class Pool
{
    public:
        Pool()
        {

FEATURE scene.h/TearDown
        }
        ~Pool()
        {

FEATURE scene.h/Impl
        }

    private:
        std::map<std::string, osg::ref_ptr<osg::MatrixTransform> > nodes;

FEATURE scene.h/End
};
