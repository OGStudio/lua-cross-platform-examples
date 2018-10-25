# NOTE This is a common CMakeLists.txt to be included by each platform's
# NOTE specific CMakeLists.txt.
# This CMakeLists.txt requires the following variables:
# * LCPE_DIR
# This CMakeLists.txt provides the following variables outside:
# * OSGCPE_DIR
# * EXAMPLE_BINARY_NAME
# * LCPE_LINK_LIBS

PROJECT(LCPE02_COLORFUL_NODE)
SET(EXAMPLE_BINARY_NAME "lcpe02-colorful-node")
SET(OSGCPE_DIR ${LCPE_DIR}/../openscenegraph-cross-platform-examples)

# Build OpenSceneGraph statically.
INCLUDE(${OSGCPE_DIR}/libs/OpenSceneGraph/CMakeLists.txt)
# Build Lua statically.
INCLUDE(${OSGCPE_DIR}/libs/lua/CMakeLists.txt)
# Reference Sol2 header-only library.
INCLUDE_DIRECTORIES(${LCPE_DIR}/../sol2)

# Reference resources.
INCLUDE_DIRECTORIES(${LCPE_DIR}/data)

# Provide libraries to link with.
SET(
    LCPE_LINK_LIBS
    osgViewer
    osgUtil
    osgDB
    # osgDB plugins start.
    osgdb_osg
    osgdb_serializers_osg
    # osgDB plugins end.
    osgGA
    osg
    OpenThreads
)
