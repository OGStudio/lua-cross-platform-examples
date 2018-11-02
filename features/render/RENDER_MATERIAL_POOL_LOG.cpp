FEATURE render.h/Impl
#include "log.h"
#include "format.h"
#define RENDER_MATERIAL_POOL_LOG_PREFIX "render::MaterialPool(%p) %s"
#define RENDER_MATERIAL_POOL_LOG(...) \
    log::logprintf( \
        RENDER_MATERIAL_POOL_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
