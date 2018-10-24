FEATURE main.h/Include
#include "render.h"

FEATURE main.h/Setup
this->setupMaterialPool();

FEATURE main.h/TearDown
this->tearMaterialPoolDown();

FEATURE main.h/Impl
public:
    render::MaterialPool *materialPool;
private:
    void setupMaterialPool()
    {
        this->materialPool = new render::MaterialPool;
    }
    void tearMaterialPoolDown()
    {
        delete this->materialPool;
    }
