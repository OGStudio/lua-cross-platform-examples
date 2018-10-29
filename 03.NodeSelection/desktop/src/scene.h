
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

// degreesToQuaternion Start
//! Convert from degrees to quaternion.
osg::Quat degreesToQuaternion(const osg::Vec3f &degrees)
{
    osg::Quat q;
    q.makeRotate(
        osg::DegreesToRadians(degrees.x()), osg::Vec3(1, 0, 0),
        osg::DegreesToRadians(degrees.y()), osg::Vec3(0, 1, 0),
        osg::DegreesToRadians(degrees.z()), osg::Vec3(0, 0, 1)
    );
    return q;
}
// degreesToQuaternion End
// quaternionToDegrees Start
osg::Vec3f quaternionToDegrees(const osg::Quat &quaternion)
{
    double q0 = quaternion.x();
    double q1 = quaternion.y();
    double q2 = quaternion.z();
    double q3 = quaternion.w();
    
    //double sq0 = q0 * q0;
    double sq1 = q1 * q1;
    double sq2 = q2 * q2;
    double sq3 = q3 * q3;
    
    double term1 = 2*(q0*q1 + q2*q3);
    double term2 = 1 - 2 * (sq1 + sq2);
    double term3 = 2 * (q0*q2 - q3*q1);
    double term4 = 2 * (q0*q3 + q1*q2);
    double term5 = 1 - 2 * (sq2 + sq3);

    double z = atan2(term1, term2);
    double y = asin(term3);
    double x = atan2(term4, term5);

    osg::Vec3f result(x * 180.0 / M_PI, y * 180.0 / M_PI, z * 180.0 / M_PI);
    // Fix for X when Y = 0.
    result.x() = 180 - result.x();
    // Fix for Z when Y = 0.
    if (result.z() < 0)
    {
        result.z() = 360 + result.z();
    }
    return result;
}
// quaternionToDegrees End
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

// nodeAtPosition Start
//! Pick node at the specified position using camera's point of view

// \param excludedNodeMask Take the node into consideration if it excludes specified mask.
osg::Node *nodeAtPosition(
    const osg::Vec2f &position,
    osg::Camera *camera,
    unsigned int excludedNodeMask
) {
    // Find intersections.
    osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
        new osgUtil::LineSegmentIntersector(
            osgUtil::Intersector::WINDOW,
            position.x(),
            position.y()
        );
    osgUtil::IntersectionVisitor iv(intersector.get());
    camera->accept(iv);

    // No intersections found.
    if (!intersector->containsIntersections())
    {
        return 0;
    }

    // Get closest intersection.
    auto intersection = intersector->getFirstIntersection();
    for (auto node : intersection.nodePath)
    {
        // Make sure node mask is excluded.
        if ((node->getNodeMask() & excludedNodeMask) != excludedNodeMask)
        {
            return node;
        }
    }

    return 0;
}
// nodeAtPosition End


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
            node->setName(name);
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
            sphere->setName(name);
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

