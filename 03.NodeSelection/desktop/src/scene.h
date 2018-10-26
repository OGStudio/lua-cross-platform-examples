
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
// simplePosition Start
#include <osg/MatrixTransform>

// simplePosition End
// setSimplePosition Start
#include <osg/MatrixTransform>

// setSimplePosition End

// Pool Start
#include <osg/MatrixTransform>

// Pool End

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

// setSimplePosition Start
//! Set node position.
//! NOTE Only works for non-rotated/scaled nodes.
void setSimplePosition(osg::MatrixTransform *node, const osg::Vec3f &position)
{
    auto matrix = node->getMatrix();
    node->setMatrix(
        osg::Matrix::scale(matrix.getScale()) *
        osg::Matrix::rotate(matrix.getRotate()) *
        osg::Matrix::translate(position)
    );
}
// setSimplePosition End
// simplePosition Start
//! Get node position.
//! NOTE Only works for non-rotated/scaled nodes.
osg::Vec3f simplePosition(osg::MatrixTransform *node)
{
    return node->getMatrix().getTrans();
}
// simplePosition End



// Pool Start
class Pool
{
    public:
        Pool()
        {

// Pool End
            // Pool+Root Start
            this->setupRoot();
            
            // Pool+Root End
// Pool Start
        }
        ~Pool()
        {

// Pool End
// Pool Start
        }

    private:
        std::map<std::string, osg::ref_ptr<osg::MatrixTransform> > nodes;

// Pool End
    // Pool+Root Start
    private:
        void setupRoot()
        {
            auto root = new osg::MatrixTransform;
            this->nodes["root"] = root;
        }
    // Pool+Root End

    // Pool+createNode Start
    public:
        osg::MatrixTransform *createNode(const std::string &name)
        {
            auto node = new osg::MatrixTransform;
            this->nodes[name] = node;
            return node;
        }
    // Pool+createNode End
    // Pool+createSphere Start
    public:
        osg::MatrixTransform *createSphere(
            const std::string &name,
            float radius
        ) {
            auto sphere = scene::createSphere(radius);
            this->nodes[name] = sphere;
            return sphere;
        }
    // Pool+createSphere End
    // Pool+node Start
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
    // Pool+node End
// Pool Start
};
// Pool End

} // namespace scene
} // namespace lcpe

#endif // LUA_CROSS_PLATFORM_EXAMPLES_SCENE_H

