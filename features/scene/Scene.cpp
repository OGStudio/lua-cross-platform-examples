FEATURE scene.h/Include
#include <osg/MatrixTransform>

FEATURE scene.h/Setup
class Scene
{
    public:
        Scene()
        {

FEATURE scene.h/TearDown
        }
        ~Scene()
        {

FEATURE scene.h/Impl
        }

    private:
        std::map<std::string, osg::ref_ptr<osg::MatrixTransform> > nodes;

FEATURE scene.h/End
};
