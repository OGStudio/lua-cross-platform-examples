FEATURE main.h/Include
#include "scene.h"

FEATURE main.h/Setup
this->setupNodePool();

FEATURE main.h/TearDown
this->tearNodePoolDown();

FEATURE main.h/Impl
public:
    scene::Pool *nodePool;
private:
    void setupNodePool()
    {
        this->nodePool = new scene::Pool;

        // Set pool's root node to viewer.
        auto root = this->nodePool->node("root");
        this->setScene(root);
    }
    void tearNodePoolDown()
    {
        this->setScene(0);
        delete this->nodePool;
    }
