FEATURE main.h/Setup
this->setupToggleBackgroundColorTest();

FEATURE main.h/TearDown
this->tearToggleBackgroundColorTestDown();

FEATURE main.h/Impl
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
