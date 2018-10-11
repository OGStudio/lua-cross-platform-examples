
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

#ifndef LUA_CROSS_PLATFORM_EXAMPLES_MAIN_H
#define LUA_CROSS_PLATFORM_EXAMPLES_MAIN_H

// FEATURE Application+frame+Reporting/Include
// FEATURE Application+handleEvent-web/Include
// FEATURE Application+setupWindow-web/Include

// FEATURE Application+HTTPClient/Include
// FEATURE Application+Logging/Include
// FEATURE Application+Mouse/Include
// FEATURE Application+Rendering/Include
// FEATURE Application+WindowResizing-web/Include

// FEATURE Example+ScriptingEnvironment/Include
// FEATURE Example+VBO/Include

// FEATURE MAIN_APPLICATION_LOG/Impl
// FEATURE MAIN_EXAMPLE_LOG/Impl

// FEATURE Example+StaticPluginOSG/Impl
// FEATURE Example+StaticPluginPNG/Impl

namespace lcpe
{
namespace main
{

// FEATURE Application/Setup
            // FEATURE Application+Logging/Setup
            // FEATURE Application+Rendering/Setup
            // FEATURE Application+Mouse/Setup
            // FEATURE Application+HTTPClient/Setup
            // FEATURE Application+HTTPClientProcessor/Setup
            // FEATURE Application+WindowResizing-web/Setup
// FEATURE Application/TearDown
            // FEATURE Application+HTTPClientProcessor/TearDown
            // FEATURE Application+HTTPClient/TearDown
            // FEATURE Application+Mouse/TearDown
            // FEATURE Application+Rendering/TearDown
            // FEATURE Application+Logging/TearDown
// FEATURE Application/Impl
    // FEATURE Application+camera/Impl
    // FEATURE Application+frame+Reporting/Impl
    // FEATURE Application+handleEvent-web/Impl
    // FEATURE Application+handleMousePress-android/Impl
    // FEATURE Application+run/Impl
    // FEATURE Application+setupWindow-desktop/Impl
    // FEATURE Application+setupWindow-embedded/Impl
    // FEATURE Application+setupWindow-ios/Impl
    // FEATURE Application+setupWindow-web/Impl

    // FEATURE Application+HTTPClient/Impl
    // FEATURE Application+HTTPClientProcessor/Impl
    // FEATURE Application+Logging/Impl
    // FEATURE Application+Mouse/Impl
    // FEATURE Application+Rendering/Impl
    // FEATURE Application+WindowResizing-web/Impl
// FEATURE Application/End

// FEATURE Example+01/Title
// FEATURE Example+02/Title
// FEATURE Example+03/Title
// FEATURE Example+04/Title
// FEATURE Example+05/Title

// FEATURE Example/Setup
        // FEATURE Example+Parameters/Setup
        // FEATURE Example+VBO/Setup
        // FEATURE Example+ScriptingEnvironment/Setup
        // FEATURE Example+application.camera.clearColor/Setup
        // FEATURE Example+ToggleBackgroundColorTest/Setup
// FEATURE Example/TearDown
        // FEATURE Example+ToggleBackgroundColorTest/TearDown
        // FEATURE Example+application.camera.clearColor/TearDown
        // FEATURE Example+ScriptingEnvironment/TearDown
// FEATURE Example/Impl
    // FEATURE Example+Parameters/Impl
    // FEATURE Example+ScriptingEnvironment/Impl
    // FEATURE Example+ToggleBackgroundColorTest/Impl
    // FEATURE Example+VBO/Impl

    // FEATURE Example+application.camera.clearColor/Impl
// FEATURE Example/End

} // namespace main
} // namespace lcpe

#endif // LUA_CROSS_PLATFORM_EXAMPLES_MAIN_H

