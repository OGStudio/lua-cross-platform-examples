
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

// Application+Logging Start
#include "log.h"

// Application+Logging End
// Application+Mouse Start
#include "input.h"

// Application+Mouse End
// Application+Rendering Start
#include "render.h"

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

// Application+Rendering End

// Example+ScriptingEnvironment Start
#include "script.h"
#include <sol.hpp>

// Example+ScriptingEnvironment End

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
            // Application+Mouse Start
            this->setupMouse();
            
            // Application+Mouse End
// Application Start
        }
        ~Application()
        {

// Application End
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
// Application Start
};
// Application End

// Example+01 Start
const auto EXAMPLE_TITLE = "LCPE-01: Toggle background color";
// Example+01 End

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
        // Example+application.camera.clearColor Start
        this->setupApplicationCameraClearColor();
        
        // Example+application.camera.clearColor End
        // Example+ToggleBackgroundColorTest Start
        this->setupToggleBackgroundColorTest();
        
        // Example+ToggleBackgroundColorTest End
// Example Start
    }
    ~Example()
    {

// Example End
        // Example+ToggleBackgroundColorTest Start
        this->tearToggleBackgroundColorTestDown();
        
        // Example+ToggleBackgroundColorTest End
        // Example+application.camera.clearColor Start
        this->tearApplicationCameraClearColorDown();
        
        // Example+application.camera.clearColor End
        // Example+ScriptingEnvironment Start
        this->tearScriptingEnvironmentDown();
        
        // Example+ScriptingEnvironment End
// Example Start
        delete this->app;
    }

// Example End
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
                // 'addClient' method.
                "addClient",
                &script::Environment::addClient,
                // 'call' method.
                "call",
                [](script::Environment &env, const std::string &key, sol::nested<script::EnvironmentClient::Values> values)
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
                                sol::nested<script::EnvironmentClient::Values> result = luaCallback(key, sol::as_table(values));
                                return std::move(result.source);
                            );
                    }
                ),
                // 'respondsToKey' method.
                "respondsToKey",
                &script::EnvironmentClient::respondsToKey
            );
        }
        void tearScriptingEnvironmentDown()
        {
            delete this->lua;
            delete this->environment;
        }
    // Example+ScriptingEnvironment End
    // Example+ToggleBackgroundColorTest Start
    private:
        void setupToggleBackgroundColorTest()
        {
            this->setupApplicationCameraClearColor();
            this->loadInternalScript();
        }
        void tearToggleBackgroundColorTestDown()
        {
            this->tearApplicationCameraClearColorDown();
        }
    
        // Script loading.
    
        void loadInternalScript()
        {
            MAIN_EXAMPLE_LOG("Loading internal script");
            auto contents = R"(
    
    print("Set background color")
    ENV:call("application.camera.clearColor", {0.5, 0.5, 0.5})
    
            )";
            // Execute the script.
            this->lua->script(contents);
            MAIN_EXAMPLE_LOG("Successfully loaded internal script");
        }
        /*
         * TODO Consider extracting it into a separate feature in OSGCPE?
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
        */
    // Example+ToggleBackgroundColorTest End

    // Example+application.camera.clearColor Start
    private:
        script::EnvironmentClient *applicationCameraClearColorClient;
        const std::string applicationCameraClearColorKey =
            "application.camera.clearColor";
    
        void setupApplicationCameraClearColor()
        {
            this->applicationCameraClearColorClient = new script::EnvironmentClient;
            this->environment->addClient(this->applicationCameraClearColorClient);
    
            this->applicationCameraClearColorClient->respondsToKey =
                SCRIPT_ENVIRONMENT_CLIENT_RESPONDS_TO_KEY(
                    return key == this->applicationCameraClearColorKey;
                );
            this->applicationCameraClearColorClient->call =
                SCRIPT_ENVIRONMENT_CLIENT_CALL(
                    return this->processApplicationCameraClearColor(key, values);
                );
        }
        void tearApplicationCameraClearColorDown()
        {
            delete this->applicationCameraClearColorClient;
        }
        script::EnvironmentClient::Values processApplicationCameraClearColor(
            const std::string &key,
            const script::EnvironmentClient::Values &values
        ) {
            auto camera = this->app->camera();
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
                    script::EnvironmentClient::Values empty;
                    return empty;
                }
    
                // Apply color.
                auto color = camera->getClearColor();
                color.r() = atof(values[0].c_str());
                color.g() = atof(values[1].c_str());
                color.b() = atof(values[2].c_str());
                camera->setClearColor(color);
            }
    
            // Return current color for Get and after successful Set.
            auto color = camera->getClearColor();
            return {
                format::printfString("%f", color.r()),
                format::printfString("%f", color.g()),
                format::printfString("%f", color.b()),
            };
        }
    // Example+application.camera.clearColor End
// Example Start
};
// Example End

} // namespace main
} // namespace lcpe

#endif // LUA_CROSS_PLATFORM_EXAMPLES_MAIN_H

