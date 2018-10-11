FEATURE main.h/Setup
this->setupToggleBackgroundColorTest();

FEATURE main.h/TearDown
this->tearToggleBackgroundColorTestDown();

FEATURE main.h/Impl
private:
    void setupToggleBackgroundColorTest()
    {
        //this->setupCameraRepresentation();
        this->loadInternalScript();
    }
    void tearToggleBackgroundColorTestDown()
    {
        //this->tearCameraRepresentationDown();
    }

    // Script loading.

    void loadInternalScript()
    {
        MAIN_EXAMPLE_LOG("Loading internal script");
        auto contents = R"(

print("This is a lua message");


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

    // Camera representation.

/*
    script::EnvironmentClient *cameraClient;
    const std::string cameraKeyPrefix = "application.camera.";

    void setupCameraRepresentation()
    {
        this->cameraClient = new script::EnvironmentClient;
        this->environment->addClient(this->cameraClient);
        this->cameraClient->respondsToKey =
            SCRIPT_ENVIRONMENT_CLIENT_RESPONDS_TO_KEY(
                return format::stringStartsWith(key, this->cameraKeyPrefix);
            );
        this->cameraClient->call =
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                return this->processCamera(key, values);
            );
    }
    void tearCameraRepresentationDown()
    {
        delete this->cameraClient;
    }
    script::EnvironmentClient::Values processCamera(
        const std::string &key,
        const script::EnvironmentClient::Values &values
    ) {
        auto cameraKey = key.substr(this->cameraKeyPrefix.length());
        script::EnvironmentClient::Values empty;
        if (cameraKey == "clearColor")
        {
            // Set.
            if (!values.empty())
            {
                // Make sure there are three components.
                if (values.size() != 3)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set key '%s' "
                        "because values' count is not 3"
                    );
                    return empty;
                }

                // Apply color.
                auto color = this->app->camera()->getClearColor();
                color.r() = atof(values[0].c_str());
                color.g() = atof(values[1].c_str());
                color.b() = atof(values[2].c_str());
                this->app->camera()->setClearColor(color);
            }

            // Return current color for Get and after successful Set.
            auto color = this->app->camera()->getClearColor();
            return {
                format::printfString("%f", color.r()),
                format::printfString("%f", color.g()),
                format::printfString("%f", color.b()),
            };
        }

        MAIN_EXAMPLE_LOG(
            "ERROR No camera handler for key '%s'",
            key.c_str()
        );
        return empty;
    }
    */
