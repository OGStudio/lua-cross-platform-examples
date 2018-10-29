
--[[
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
--]]

-- Library domain begins --

core = {}

-- FEATURE core.PropertiesMT/Impl
-- FEATURE core.Reporter/Impl

render = {}

-- FEATURE render.Material/Start
        -- FEATURE render.Material.setShaders/Impl
        -- FEATURE render.Material.setUniform/Impl
-- FEATURE render.Material/End

resource = {}

-- FEATURE resource.Resource/Start
-- FEATURE resource.Resource/End

scene = {}

-- FEATURE scene.Node/Methods
        -- FEATURE scene.Node.addChild/Impl
        -- FEATURE scene.Node.setMask/Impl
        -- FEATURE scene.Node.setMaterial/Impl
-- FEATURE scene.Node/Properties
    -- FEATURE scene.Node.position/Impl
-- FEATURE scene.Node/End

main = {}

-- FEATURE main.application/Impl

-- FEATURE main.application.camera/Methods
    -- FEATURE main.application.camera.nodeAtPosition/Impl
-- FEATURE main.application.camera/Properties
    -- FEATURE main.application.camera.clearColor/Impl
    -- FEATURE main.application.camera.position/Impl
    -- FEATURE main.application.camera.rotation/Impl

-- FEATURE main.application.materialPool/Impl
-- FEATURE main.application.materialPool.createMaterial/Impl
-- FEATURE main.application.mouse/Impl
-- FEATURE main.application.nodePool/Impl
-- FEATURE main.application.nodePool.createNode/Impl
-- FEATURE main.application.nodePool.createSphere/Impl
-- FEATURE main.application.nodePool.node/Impl
-- FEATURE main.application.parameters/Impl
-- FEATURE main.application.resourcePool/Impl
-- FEATURE main.application.resourcePool.loadResource/Impl
-- FEATURE main.application.resourcePool.resource/Impl
-- FEATURE main.application.resourcePool.setLocations/Impl

-- Library domain ends --

-- Example domain begins --

-- FEATURE testBackgroundColorToggle/Impl
-- FEATURE testColorfulNodes/Impl
-- FEATURE testNodeSelection/Impl

-- Example domain ends --

