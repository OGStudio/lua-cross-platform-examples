
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

// Application+frame+Reporting Start
#include "core.h"

// Application+frame+Reporting End

// Application+CameraManipulator Start
#include <osgGA/TrackballManipulator>

// Application+CameraManipulator End
// Application+HTTPClient Start
#include "network.h"

// Application+HTTPClient End
// Application+Logging Start
#include "log.h"

// Application+Logging End
// Application+MaterialPool Start
#include "render.h"

// Application+MaterialPool End
// Application+Mouse Start
#include "input.h"

// Application+Mouse End
// Application+NodePool Start
#include "scene.h"

// Application+NodePool End
// Application+Rendering Start
#include "render.h"

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

// Application+Rendering End
// Application+ResourcePool Start
#include "resource.h"

// Application+ResourcePool End

// Example+loadCLIScript Start
#include <fstream>

// Example+loadCLIScript End

// Example+ScriptingEnvironment Start
#include "script.h"
#include <sol.hpp>

// Example+ScriptingEnvironment End

// MAIN_EXAMPLE_ENVIRONMENT_FUNCTION Start
#define MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(NAME) \
    std::vector<std::string> NAME ( \
        const std::string &key, \
        const std::vector<std::string> &values \
    )
// MAIN_EXAMPLE_ENVIRONMENT_FUNCTION End
// MAIN_EXAMPLE_LOG Start
#include "log.h"
#include "format.h"
#define MAIN_EXAMPLE_LOG_PREFIX "main::Example(%p) %s"
#define MAIN_EXAMPLE_LOG(...) \
    log::logprintf( \
        MAIN_EXAMPLE_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
// MAIN_EXAMPLE_LOG End
// MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT Start
#define MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(KEYS, FUNC) \
    auto client = new script::EnvironmentClient; \
    this->environment->addClient(client, KEYS); \
    client->call = SCRIPT_ENVIRONMENT_CLIENT_CALL(return FUNC(key,values);); \
    this->environmentClients.push_back(client);
// MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT End


namespace lcpe
{
namespace main
{

// Application Start
class Application
{
    public:
        Application(const std::string &name)
        {

// Application End
            // Application+Logging Start
            this->setupLogging(name);
            
            // Application+Logging End
            // Application+Rendering Start
            this->setupRendering();
            
            // Application+Rendering End
            // Application+CameraManipulator Start
            this->setupCameraManipulator();
            
            // Application+CameraManipulator End
            // Application+Mouse Start
            this->setupMouse();
            
            // Application+Mouse End
            // Application+NodePool Start
            this->setupNodePool();
            
            // Application+NodePool End
            // Application+MaterialPool Start
            this->setupMaterialPool();
            
            // Application+MaterialPool End
            // Application+ResourcePool Start
            this->setupResourcePool();
            
            // Application+ResourcePool End
            // Application+HTTPClient Start
            this->setupHTTPClient();
            
            // Application+HTTPClient End
            // Application+HTTPClientProcessor Start
            this->setupHTTPClientProcessor();
            
            // Application+HTTPClientProcessor End
// Application Start
        }
        ~Application()
        {

// Application End
            // Application+HTTPClientProcessor Start
            this->tearHTTPClientProcessorDown();
            
            // Application+HTTPClientProcessor End
            // Application+HTTPClient Start
            this->tearHTTPClientDown();
            
            // Application+HTTPClient End
            // Application+MaterialPool Start
            this->tearMaterialPoolDown();
            
            // Application+MaterialPool End
            // Application+NodePool Start
            this->tearNodePoolDown();
            
            // Application+NodePool End
            // Application+ResourcePool Start
            this->tearResourcePoolDown();
            
            // Application+ResourcePool End
            // Application+Mouse Start
            this->tearMouseDown();
            
            // Application+Mouse End
            // Application+Rendering Start
            this->tearRenderingDown();
            
            // Application+Rendering End
            // Application+Logging Start
            this->tearLoggingDown();
            
            // Application+Logging End
// Application Start
        }

// Application End
    // Application+camera Start
    public:
        osg::Camera *camera()
        {
            return this->viewer->getCamera();
        }
    // Application+camera End
    // Application+frame+Reporting Start
    public:
        core::Reporter frameReporter;
        void frame()
        {
            this->viewer->frame();
            this->frameReporter.report();
        }
    // Application+frame+Reporting End
    // Application+run Start
    public:
        void run()
        {
            while (!this->viewer->done())
            {
                this->frame();
            }
        }
    // Application+run End
    // Application+setupWindow-desktop Start
    public:
        void setupWindow(
            const std::string &title,
            int x,
            int y,
            int width,
            int height
        ) {
            osg::GraphicsContext *gc =
                render::createGraphicsContext(title, x, y, width, height);
            // Configure viewer's camera with FOVY and window size.
            osg::Camera *cam = this->viewer->getCamera();
            render::setupCamera(cam, gc, 30, width, height);
        }
    // Application+setupWindow-desktop End

    // Application+CameraManipulator Start
    private:
        osg::ref_ptr<osgGA::TrackballManipulator> cameraManip;
        void setupCameraManipulator()
        {
            // Create manipulator: CRITICAL for mobile and web.
            this->cameraManip = new osgGA::TrackballManipulator;
            this->viewer->setCameraManipulator(this->cameraManip);
        }
    public:
        osgGA::TrackballManipulator *cameraManipulator()
        {
            return this->cameraManip;
        }
    // Application+CameraManipulator End
    // Application+HTTPClient Start
    public:
        network::HTTPClient *httpClient;
    private:
        void setupHTTPClient()
        {
            this->httpClient = new network::HTTPClient;
        }
        void tearHTTPClientDown()
        {
            delete this->httpClient;
        }
    // Application+HTTPClient End
    // Application+HTTPClientProcessor Start
    public:
        network::HTTPClientProcessor *httpClientProcessor;
    private:
        const std::string httpClientProcessorCallbackName = "HTTPClientProcessor";
    
        void setupHTTPClientProcessor()
        {
            this->httpClientProcessor = new network::HTTPClientProcessor(this->httpClient);
            // Subscribe processor to be processed each frame.
            this->frameReporter.addCallback(
                [&] {
                    this->httpClientProcessor->process();
                },
                this->httpClientProcessorCallbackName
            );
        }
        void tearHTTPClientProcessorDown()
        {
            this->frameReporter.removeCallback(this->httpClientProcessorCallbackName);
            delete this->httpClientProcessor;
        }
    // Application+HTTPClientProcessor End
    // Application+Logging Start
    private:
        log::Logger *logger;
        void setupLogging(const std::string &appName)
        {
            // Create custom logger.
            this->logger = new log::Logger(appName);
            // Provide the logger to OpenSceneGraph.
            osg::setNotifyHandler(this->logger);
            // Only accept notifications of Info level or higher
            // like warnings and errors.
            //osg::setNotifyLevel(osg::INFO);
            osg::setNotifyLevel(osg::WARN);
        }
        void tearLoggingDown()
        {
            // Remove the logger from OpenSceneGraph.
            // This also destroys the logger: no need to deallocate it manually.
            osg::setNotifyHandler(0);
        }
    // Application+Logging End
    // Application+MaterialPool Start
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
    // Application+MaterialPool End
    // Application+Mouse Start
    public:
        osg::ref_ptr<input::Mouse> mouse;
    private:
        void setupMouse()
        {
            // Create mouse events' handler.
            this->mouse = new input::Mouse;
            // Register it.
            this->viewer->addEventHandler(this->mouse);
        }
        void tearMouseDown()
        {
            // This also removes Mouse instance.
            this->viewer->removeEventHandler(this->mouse);
        }
    // Application+Mouse End
    // Application+NodePool Start
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
    // Application+NodePool End
    // Application+Rendering Start
    public:
        void setScene(osg::Node *scene)
        {
            // Make sure we reset the scene upon setting the same scene again.
            this->viewer->setSceneData(0);
            this->viewer->setSceneData(scene);
        }
    private:
        osgViewer::Viewer *viewer;
        void setupRendering()
        {
            // Create OpenSceneGraph viewer.
            this->viewer = new osgViewer::Viewer;
            // Use single thread: CRITICAL for mobile and web.
            this->viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
            // Create manipulator: CRITICAL for mobile and web.
            this->viewer->setCameraManipulator(new osgGA::TrackballManipulator);
        }
        void tearRenderingDown()
        {
            delete this->viewer;
        }
    // Application+Rendering End
    // Application+ResourcePool Start
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
    // Application+ResourcePool End
// Application Start
};
// Application End

// Example+03 Start
const auto EXAMPLE_TITLE = "LCPE-03: Node selection";
// Example+03 End

// Example Start
struct Example
{
    Application *app;

    typedef std::map<std::string, std::string> Parameters;

    Example(const Parameters &parameters)
    {
        this->app = new Application(EXAMPLE_TITLE);

// Example End
        // Example+Parameters Start
        this->setupParameters(parameters);
        
        // Example+Parameters End
        // Example+ScriptingEnvironment Start
        this->setupScriptingEnvironment();
        
        // Example+ScriptingEnvironment End
        // Example+application.camera.nodeAtPosition Start
        this->setup_application_camera_nodeAtPosition();
        
        // Example+application.camera.nodeAtPosition End
        // Example+application.camera.position Start
        this->setup_application_camera_position();
        
        // Example+application.camera.position End
        // Example+application.camera.rotation Start
        this->setup_application_camera_rotation();
        
        // Example+application.camera.rotation End
        // Example+application.materialPool.createMaterial Start
        this->setup_application_materialPool_createMaterial();
        
        // Example+application.materialPool.createMaterial End
        // Example+application.materialPool.material.setShaders Start
        this->setup_application_materialPool_material_setShaders();
        
        // Example+application.materialPool.material.setShaders End
        // Example+application.materialPool.material.setUniform Start
        this->setup_application_materialPool_material_setUniform();
        
        // Example+application.materialPool.material.setUniform End
        // Example+application.mouse Start
        this->setupApplicationMouse();
        
        // Example+application.mouse End
        // Example+application.nodePool.createNode Start
        this->setup_application_nodePool_createNode();
        
        // Example+application.nodePool.createNode End
        // Example+application.nodePool.createSphere Start
        this->setup_application_nodePool_createSphere();
        
        // Example+application.nodePool.createSphere End
        // Example+application.nodePool.node.addChild Start
        this->setup_application_nodePool_node_addChild();
        
        // Example+application.nodePool.node.addChild End
        // Example+application.nodePool.node.exists Start
        this->setup_application_nodePool_node_exists();
        
        // Example+application.nodePool.node.exists End
        // Example+application.nodePool.node.setMask Start
        this->setup_application_nodePool_node_setMask();
        
        // Example+application.nodePool.node.setMask End
        // Example+application.nodePool.node.setMaterial Start
        this->setup_application_nodePool_node_setMaterial();
        
        // Example+application.nodePool.node.setMaterial End
        // Example+application.nodePool.node.position Start
        this->setup_application_nodePool_node_position();
        
        // Example+application.nodePool.node.position End
        // Example+application.parameters Start
        this->setup_application_parameters();
        
        // Example+application.parameters End
        // Example+application.resourcePool.loadResource Start
        this->setup_application_resourcePool_loadResource();
        
        // Example+application.resourcePool.loadResource End
        // Example+application.resourcePool.locations Start
        this->setup_application_resourcePool_locations();
        
        // Example+application.resourcePool.locations End
        // Example+application.resourcePool.resource.exists Start
        this->setup_application_resourcePool_resource_exists();
        
        // Example+application.resourcePool.resource.exists End
        // Example+LoadScriptTest Start
        this->setupLoadScriptTest();
        
        // Example+LoadScriptTest End
// Example Start
    }
    ~Example()
    {

// Example End
        // Example+ScriptingEnvironment Start
        this->tearScriptingEnvironmentDown();
        
        // Example+ScriptingEnvironment End
        // Example+EnvironmentClients Start
        this->tearEnvironmentClientsDown();
        
        // Example+EnvironmentClients End
        // Example+application.mouse Start
        this->tearApplicationMouseDown();
        
        // Example+application.mouse End
// Example Start
        delete this->app;
    }

// Example End
    // Example+loadCLIScript Start
    private:
        void loadCLIScript()
        {
            // Make sure `script` parameter exists.
            auto it = this->parameters.find("script");
            if (it == this->parameters.end())
            {
                return;
            }
    
            auto path = it->second;
            MAIN_EXAMPLE_LOG("Loading script '%s'", path.c_str());
            std::ifstream localScript(path);
            if (localScript)
            {
                // Read file contents into string.
                std::string fileContents(
                    (std::istreambuf_iterator<char>(localScript)),
                    (std::istreambuf_iterator<char>())
                );
                // Execute the script.
                this->lua->script(fileContents);
                MAIN_EXAMPLE_LOG("Successfully loaded local script");
            }
            else
            {
                MAIN_EXAMPLE_LOG("ERROR Could not read local script");
            }
        }
    // Example+loadCLIScript End

    // Example+EnvironmentClients Start
    private:
        std::vector<script::EnvironmentClient *> environmentClients;
        void tearEnvironmentClientsDown()
        {
            for (auto client : this->environmentClients)
            {
                delete client;
            }
            this->environmentClients.clear();
        }
    // Example+EnvironmentClients End
    // Example+LoadScriptTest Start
    private:
        void setupLoadScriptTest()
        {
            this->loadCLIScript();
        }
    // Example+LoadScriptTest End
    // Example+Parameters Start
    private:
        Parameters parameters;
        void setupParameters(const Parameters &parameters)
        {
            this->parameters = parameters;
        }
    // Example+Parameters End
    // Example+ScriptingEnvironment Start
    private:
        script::Environment *environment;
        sol::state *lua;
    
        void setupScriptingEnvironment()
        {
            this->environment = new script::Environment;
    
            this->lua = new sol::state;
            this->lua->open_libraries();
            // Register Environment instance.
            (*this->lua)["ENV"] = this->environment;
            // Register Environment class.
            this->lua->new_usertype<script::Environment>(
                "Environment",
                // 'setVerbose' method.
                "setVerbose",
                [](script::Environment &env, bool state)
                {
                    env.setVerbose(state);
                },
                // 'addClient' method.
                "addClient",
                [](script::Environment &env, script::EnvironmentClient *client, sol::nested<std::vector<std::string> > keys)
                {
                    env.addClient(client, keys);
                },
                //&script::Environment::addClient,
                // 'call' method.
                "call",
                [](script::Environment &env, const std::string &key, sol::nested<std::vector<std::string> > values)
                {
                    return env.call(key, values);
                }
            );
            // Register EnvironmentClient class.
            this->lua->new_usertype<script::EnvironmentClient>(
                "EnvironmentClient",
                // 'call' method.
                "call",
                sol::property(
                    [](script::EnvironmentClient &ec, sol::function luaCallback)
                    {
                        ec.call =
                            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                                sol::nested<std::vector<std::string> > result =
                                    luaCallback(key, sol::as_table(values));
                                return std::move(result.source);
                            );
                    }
                )
            );
        }
        void tearScriptingEnvironmentDown()
        {
            delete this->lua;
            delete this->environment;
        }
    // Example+ScriptingEnvironment End

    // Example+application.camera.nodeAtPosition Start
    private:
        void setup_application_camera_nodeAtPosition()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.camera.nodeAtPosition"
                },
                this->process_application_camera_nodeAtPosition
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_camera_nodeAtPosition)
        {
            // Make sure there are three components.
            if (values.size() != 3)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 3"
                );
                return { };
            }
    
            osg::Vec2d position = {
                atof(values[0].c_str()),
                atof(values[1].c_str()),
            };
            int selectionMask = atoi(values[2].c_str());
    
            // Locate a node.
            auto node =
                scene::nodeAtPosition(
                    position,
                    this->app->camera(),
                    selectionMask
                );
    
            // Return the name of the node if it exists.
            if (node)
            {
                return { node->getName() };
            }
    
            // Return nothing otherwise.
            return { };
        }
    // Example+application.camera.nodeAtPosition End
    // Example+application.camera.position Start
    private:
        void setup_application_camera_position()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.camera.position"
                },
                this->process_application_camera_position
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_camera_position)
        {
            auto manipulator = this->app->cameraManipulator();
            osg::Vec3d pos;
            osg::Quat q;
            manipulator->getTransformation(pos, q);
    
            // Set.
            if (!values.empty())
            {
                // Make sure there are three components.
                if (values.size() != 3)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 3"
                    );
                    return { };
                }
    
                // Apply position.
                pos = {
                    atof(values[0].c_str()),
                    atof(values[1].c_str()),
                    atof(values[2].c_str()),
                };
                manipulator->setTransformation(pos, q);
            }
    
            // Return current position for Get and after Set.
            manipulator->getTransformation(pos, q);
            return {
                format::printfString("%f", pos.x()),
                format::printfString("%f", pos.y()),
                format::printfString("%f", pos.z()),
            };
        }
    // Example+application.camera.position End
    // Example+application.camera.rotation Start
    private:
        void setup_application_camera_rotation()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.camera.rotation"
                },
                this->process_application_camera_rotation
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_camera_rotation)
        {
            auto manipulator = this->app->cameraManipulator();
            osg::Vec3d pos;
            osg::Quat q;
            manipulator->getTransformation(pos, q);
    
            // Set.
            if (!values.empty())
            {
                // Make sure there are three components.
                if (values.size() != 3)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 3"
                    );
                    return { };
                }
    
                // Apply rotation.
                osg::Vec3d rot = {
                    atof(values[0].c_str()),
                    atof(values[1].c_str()),
                    atof(values[2].c_str()),
                };
                q = scene::degreesToQuaternion(rot);
                manipulator->setTransformation(pos, q);
            }
    
            // Return current position for Get and after Set.
            manipulator->getTransformation(pos, q);
            auto rot = scene::quaternionToDegrees(q);
            return {
                format::printfString("%f", rot.x()),
                format::printfString("%f", rot.y()),
                format::printfString("%f", rot.z()),
            };
        }
    // Example+application.camera.rotation End
    // Example+application.materialPool.createMaterial Start
    private:
        void setup_application_materialPool_createMaterial()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.materialPool.createMaterial"
                },
                this->process_application_materialPool_createMaterial
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_materialPool_createMaterial)
        {
            // Set.
            if (!values.empty())
            {
                // Make sure there is one component.
                if (values.size() != 1)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 1"
                    );
                    return { };
                }
    
                // Create material.
                auto pool = this->app->materialPool;
                auto name = values[0];
                pool->createMaterial(name);
            }
    
            return { };
        }
    // Example+application.materialPool.createMaterial End
    // Example+application.materialPool.material.setShaders Start
    private:
        void setup_application_materialPool_material_setShaders()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.materialPool.material.setShaders"
                },
                this->process_application_materialPool_material_setShaders
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_materialPool_material_setShaders)
        {
            // Set.
            if (!values.empty())
            {
                // Make sure there are 5 components.
                if (values.size() != 5)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 5",
                        key.c_str()
                    );
                    return { };
                }
    
                auto materialName = values[0];
                auto vertexShaderGroup = values[1];
                auto vertexShaderName = values[2];
                auto fragmentShaderGroup = values[3];
                auto fragmentShaderName = values[4];
    
                auto material = this->app->materialPool->material(materialName);
                auto vertexShader =
                    this->app->resourcePool->resource(
                        vertexShaderGroup,
                        vertexShaderName
                    );
                auto fragmentShader =
                    this->app->resourcePool->resource(
                        fragmentShaderGroup,
                        fragmentShaderName
                    );
    
                // Make sure material and shaders exist.
                if (
                    !material ||
                    !vertexShader ||
                    !fragmentShader
                ) {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set vertex shader '%s/%s' and fragment "
                        "shader '%s/%s' for material '%s' "
                        "because material and/or shader(s) do(es) not exist",
                        vertexShaderGroup.c_str(),
                        vertexShaderName.c_str(),
                        fragmentShaderGroup.c_str(),
                        fragmentShaderName.c_str(),
                        materialName.c_str()
                    );
                    return { };
                }
    
                auto prog =
                    render::createShaderProgram(
                        vertexShader->contents,
                        fragmentShader->contents
                    );
    
                material->setAttribute(prog);
            }
    
            return { };
        }
    // Example+application.materialPool.material.setShaders End
    // Example+application.materialPool.material.setUniform Start
    private:
        void setup_application_materialPool_material_setUniform()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.materialPool.material.setUniform"
                },
                this->process_application_materialPool_material_setUniform
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_materialPool_material_setUniform)
        {
            // Set.
            if (!values.empty())
            {
                // Make sure there are at least three components.
                if (values.size() < 3)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is less than 3",
                        key.c_str()
                    );
                    return { };
                }
    
                auto materialName = values[0];
                auto uniformName = values[1];
    
                // We only support vec3 values.
                // TODO Support other values, too.
                if (values.size() != 5)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Cannot set value for uniform '%s' of material '%s' "
                        "because we only support vec3 values for now",
                        uniformName.c_str(),
                        materialName.c_str()
                    );
                    return { };
                }
    
                auto material = this->app->materialPool->material(materialName);
    
                // Make sure material exists.
                if (!material)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not uniform '%s' for material '%s' "
                        "because material does not exist",
                        uniformName.c_str(),
                        materialName.c_str()
                    );
                    return { };
                }
    
                osg::Uniform *uniform =
                    material->getOrCreateUniform(
                        uniformName,
                        osg::Uniform::FLOAT_VEC3
                    );
                osg::Vec3 vector(
                    atof(values[2].c_str()),
                    atof(values[3].c_str()),
                    atof(values[4].c_str())
                );
                uniform->set(vector);
            }
    
            return { };
        }
    // Example+application.materialPool.material.setUniform End
    // Example+application.mouse Start
    private:
        const std::string applicationMousePressedButtonsKey =
            "application.mouse.pressedButtons";
        const std::string applicationMousePositionKey =
            "application.mouse.position";
        const std::string applicationMouseCallbackName =
            "ApplicationMouseTransmitter";
    
        void setupApplicationMouse()
        {
            // Transmit pressed buttons.
            this->app->mouse->pressedButtonsChanged.addCallback(
                [=] {
                    this->transmitApplicationMouseButtons();
                },
                this->applicationMouseCallbackName
            );
            // Transmit position.
            this->app->mouse->positionChanged.addCallback(
                [=] {
                    this->transmitApplicationMousePosition();
                },
                this->applicationMouseCallbackName
            );
            // NOTE We don't provide getters because Lua side
            // NOTE should keep the state itself.
            // NOTE Also, we don't provide setters because C++ side
            // NOTE has no such notion.
        }
        void tearApplicationMouseDown()
        {
            this->app->mouse->pressedButtonsChanged.removeCallback(
                this->applicationMouseCallbackName
            );
            this->app->mouse->positionChanged.removeCallback(
                this->applicationMouseCallbackName
            );
        }
        void transmitApplicationMouseButtons()
        {
            // Convert buttons to string representation.
            auto buttons = this->app->mouse->pressedButtons;
            std::vector<std::string> strbuttons;
            for (auto button : buttons)
            {
                strbuttons.push_back(mouseButtonToString(button));
            }
            // Transmit.
            this->environment->call(
                this->applicationMousePressedButtonsKey,
                strbuttons
            );
        }
        void transmitApplicationMousePosition()
        {
            // Convert position to string representation.
            auto position = this->app->mouse->position;
            std::vector<std::string> strposition = {
                format::printfString("%f", position.x()),
                format::printfString("%f", position.y()),
            };
            // Transmit.
            this->environment->call(
                this->applicationMousePositionKey,
                strposition
            );
        }
    // Example+application.mouse End
    // Example+application.nodePool.createNode Start
    private:
        void setup_application_nodePool_createNode()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.nodePool.createNode"
                },
                this->process_application_nodePool_createNode
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_createNode)
        {
            // Set.
            if (!values.empty())
            {
                // Make sure there is one component.
                if (values.size() != 1)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 1"
                    );
                    return { };
                }
    
                // Create node.
                auto pool = this->app->nodePool;
                auto name = values[0];
                pool->createNode(name);
            }
    
            return { };
        }
    // Example+application.nodePool.createNode End
    // Example+application.nodePool.createSphere Start
    private:
        void setup_application_nodePool_createSphere()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.nodePool.createSphere"
                },
                this->process_application_nodePool_createSphere
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_createSphere)
        {
            // Set.
            if (!values.empty())
            {
                // Make sure there are two components.
                if (values.size() != 2)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 2"
                    );
                    return { };
                }
    
                // Create sphere.
                auto pool = this->app->nodePool;
                auto name = values[0];
                auto radius = atof(values[1].c_str());
                pool->createSphere(name, radius);
            }
    
            return { };
        }
    // Example+application.nodePool.createSphere End
    // Example+application.nodePool.node.addChild Start
    private:
        void setup_application_nodePool_node_addChild()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.nodePool.node.addChild"
                },
                this->process_application_nodePool_node_addChild
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_addChild)
        {
            // Set.
            if (!values.empty())
            {
                // Make sure there are two components.
                if (values.size() != 2)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 2"
                    );
                    return { };
                }
    
                auto pool = this->app->nodePool;
                auto parentName = values[0];
                auto childName = values[1];
                auto parent = pool->node(parentName);
                auto child = pool->node(childName);
    
                // Make sure parent and child exist.
                if (!parent || !child)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not add '%s' child node to '%s' parent node "
                        "because of the nodes does not exist",
                        childName.c_str(),
                        parentName.c_str()
                    );
                    return { };
                }
    
                parent->addChild(child);
            }
    
            return { };
        }
    // Example+application.nodePool.node.addChild End
    // Example+application.nodePool.node.exists Start
    private:
        void setup_application_nodePool_node_exists()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.nodePool.node.exists"
                },
                this->process_application_nodePool_node_exists
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_exists)
        {
            // Set.
            if (!values.empty())
            {
                // Make sure there is one component.
                if (values.size() != 1)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 1"
                    );
                    return { };
                }
    
                auto pool = this->app->nodePool;
                auto name = values[0];
                auto node = pool->node(name);
                if (node != 0)
                {
                    return { "true" };
                }
            }
    
            return { };
        }
    // Example+application.nodePool.node.exists End
    // Example+application.nodePool.node.setMask Start
    private:
        void setup_application_nodePool_node_setMask()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.nodePool.node.setMask"
                },
                this->process_application_nodePool_node_setMask
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_setMask)
        {
            // Make sure there are two components.
            if (values.size() != 2)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is not 2"
                );
                return { };
            }
    
            auto name = values[0];
            auto node = this->app->nodePool->node(name);
    
            // Make sure node exists.
            if (!node)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set mask for node named '%s' because "
                    "it does not exist",
                    name.c_str()
                );
                return { };
            }
    
            // Set mask.
            int mask = atoi(values[1].c_str());
            node->setNodeMask(node->getNodeMask() & ~mask);
    
            return { };
        }
    // Example+application.nodePool.node.setMask End
    // Example+application.nodePool.node.setMaterial Start
    private:
        void setup_application_nodePool_node_setMaterial()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.nodePool.node.setMaterial"
                },
                this->process_application_nodePool_node_setMaterial
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_setMaterial)
        {
            // Set.
            if (!values.empty())
            {
                // Make sure there is at least one component.
                if (values.size() < 1)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is less than 1",
                        key.c_str()
                    );
                    return { };
                }
    
                auto nodeName = values[0];
                auto node = this->app->nodePool->node(nodeName);
    
                std::string materialName = "(nil)";
                osg::StateSet *material = 0;
                if (values.size() == 2)
                {
                    materialName = values[1];
                    material = this->app->materialPool->material(materialName);
                }
    
                // Make sure node exists.
                if (!node)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set material '%s' for node '%s' "
                        "because node does not exist",
                        materialName.c_str(),
                        nodeName.c_str()
                    );
                    return { };
                }
    
                node->setStateSet(material);
            }
    
            return { };
        }
    // Example+application.nodePool.node.setMaterial End
    // Example+application.nodePool.node.position Start
    private:
        void setup_application_nodePool_node_position()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.nodePool.node.position"
                },
                this->process_application_nodePool_node_position
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_nodePool_node_position)
        {
            // Make sure there is at least one component.
            if (values.size() < 1)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not set value for key '%s' "
                    "because values' count is less than 1",
                    key.c_str()
                );
                return { };
            }
    
            auto nodeName = values[0];
            auto node = this->app->nodePool->node(nodeName);
    
            // Make sure node exists.
            if (!node)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not get or set position for node '%s' "
                    "because it does not exist",
                    nodeName.c_str()
                );
                return { };
            }
    
            // Set.
            if (values.size() == 4)
            {
                osg::Vec3 position(
                    atof(values[1].c_str()),
                    atof(values[2].c_str()),
                    atof(values[3].c_str())
                );
                scene::setSimplePosition(node, position);
            }
    
            // Get.
            auto position = scene::simplePosition(node);
            return {
                format::printfString("%f", position.x()),
                format::printfString("%f", position.y()),
                format::printfString("%f", position.z()),
            };
        }
    // Example+application.nodePool.node.position End
    // Example+application.parameters Start
    private:
        void setup_application_parameters()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.parameters"
                },
                this->process_application_parameters
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_parameters)
        {
            std::vector<std::string> keysAndValues;
            for (auto parameter : this->parameters)
            {
                auto key = parameter.first;
                auto value = parameter.second;
                keysAndValues.push_back(key);
                keysAndValues.push_back(value);
            }
            return keysAndValues;
        }
    // Example+application.parameters End
    // Example+application.resourcePool.loadResource Start
    private:
        void setup_application_resourcePool_loadResource()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.resourcePool.loadResource"
                },
                this->process_application_resourcePool_loadResource
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_resourcePool_loadResource)
        {
            auto pool = this->app->resourcePool;
            // Set.
            if (!values.empty())
            {
                // Make sure there are two components.
                if (values.size() != 2)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 2"
                    );
                    return { };
                }
    
                auto group = values[0];
                auto name = values[1];
                pool->loadResource(group, name);
            }
    
            return { };
        }
    // Example+application.resourcePool.loadResource End
    // Example+application.resourcePool.locations Start
    private:
        void setup_application_resourcePool_locations()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.resourcePool.locations"
                },
                this->process_application_resourcePool_locations
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_resourcePool_locations)
        {
            auto pool = this->app->resourcePool;
            // Set.
            if (!values.empty())
            {
                pool->locations = values;
            }
    
            // Return current locations for both Get and Set.
            return pool->locations;
        }
    // Example+application.resourcePool.locations End
    // Example+application.resourcePool.resource.exists Start
    private:
        void setup_application_resourcePool_resource_exists()
        {
            MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
                {
                    "application.resourcePool.resource.exists"
                },
                this->process_application_resourcePool_resource_exists
            );
        }
        MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_resourcePool_resource_exists)
        {
            // Set.
            if (!values.empty())
            {
                // Make sure there are two components.
                if (values.size() != 2)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 2"
                    );
                    return { };
                }
    
                auto pool = this->app->resourcePool;
                auto group = values[0];
                auto name = values[1];
                auto res = pool->resource(group, name);
                if (res != 0)
                {
                    return { "true" };
                }
            }
    
            return { };
        }
    // Example+application.resourcePool.resource.exists End
// Example Start
};
// Example End

} // namespace main
} // namespace lcpe

#endif // LUA_CROSS_PLATFORM_EXAMPLES_MAIN_H

