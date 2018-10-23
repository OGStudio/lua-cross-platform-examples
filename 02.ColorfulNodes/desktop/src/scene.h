
/*
This file is part of Lua cross-platform examples:
  https://github.com/OGStudio/lua-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef LUA_CROSS_PLATFORM_EXAMPLES_SCENE_H
#define LUA_CROSS_PLATFORM_EXAMPLES_SCENE_H

// createShape Start
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>

// createShape End

// Scene Start
#include <osg/MatrixTransform>

// Scene End

namespace lcpe
{
namespace scene
{

// createShape Start
osg::MatrixTransform *createShape(osg::Shape *shape)
{
    auto hints = new osg::TessellationHints;
    hints->setDetailRatio(0.5);
    auto geode = new osg::Geode();
    geode->addDrawable(new osg::ShapeDrawable(shape, hints));
    osg::ref_ptr<osg::MatrixTransform> node = new osg::MatrixTransform;
    node->addChild(geode);
    return node.release();
}
// createShape End
// createSphere Start
osg::MatrixTransform *createSphere(float radius)
{
    auto sphere = new osg::Sphere(osg::Vec3f(0, 0, 0), radius);
    return createShape(sphere);
}
// createSphere End




// Scene Start
class Scene
{
    public:
        Scene()
        {

// Scene End
            // Scene+Root Start
            this->setupRoot();
            
            // Scene+Root End
// Scene Start
        }
        ~Scene()
        {

// Scene End
// Scene Start
        }

    private:
        std::map<std::string, osg::ref_ptr<osg::MatrixTransform> > nodes;

// Scene End
    // Scene+Root Start
    private:
        void setupRoot()
        {
            auto root = new osg::MatrixTransform;
            this->nodes["root"] = root;
        }
    // Scene+Root End

    // Scene+createSphere Start
    public:
        osg::MatrixTransform *createSphere(
            const std::string &name,
            float radius
        ) {
            auto sphere = scene::createSphere(radius);
            this->nodes[name] = sphere;
            return sphere;
        }
    // Scene+createSphere End
    // Scene+node Start
    public:
        osg::MatrixTransform *node(const std::string &name)
        {
            auto it = this->nodes.find(name);
    
            // Return valid node.
            if (it != this->nodes.end())
            {
                return it->second.get();
            }
    
            // Found noting.
            return 0;
        }
    // Scene+node End
// Scene Start
};
// Scene End

} // namespace scene
} // namespace lcpe

#endif // LUA_CROSS_PLATFORM_EXAMPLES_SCENE_H

