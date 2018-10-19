FEATURE main.h/Include
#include "resource.h"

FEATURE main.h/Setup
this->setupResourcePool();

FEATURE main.h/TearDown
this->tearResourcePoolDown();

FEATURE main.h/Impl
public:
    resource::Pool *resourcePool;
private:
    void setupResourcePool()
    {
        this->resourcePool = new resource::Pool;
    }
    void tearResourcePoolDown()
    {
        delete this->resourcePool;
    }
