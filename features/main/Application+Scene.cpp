FEATURE main.h/Include
#include "scene.h"

FEATURE main.h/Setup
this->setupScene();

FEATURE main.h/TearDown
this->tearSceneDown();

FEATURE main.h/Impl
public:
    scene::Scene *scene;
private:
    void setupScene()
    {
        this->scene = new scene::Scene;

        // Set scene's root node to viewer.
        auto root = this->scene->node("root");
        this->setScene(root);
    }
    void tearSceneDown()
    {
        this->setScene(0);
        delete this->scene;
    }
