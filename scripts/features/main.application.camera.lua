FEATURE main.lua/Methods
main.application.camera = {

FEATURE main.lua/Properties
}

-- Set metatable to have properties easily.
local cameraMT = core.createPropertiesMT()
setmetatable(main.application.camera, cameraMT)
