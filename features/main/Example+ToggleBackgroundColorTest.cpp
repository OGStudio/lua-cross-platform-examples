FEATURE main.h/Setup
this->setupToggleBackgroundColorTest();

FEATURE main.h/TearDown
this->tearToggleBackgroundColorTestDown();

FEATURE main.h/Impl
private:
    void setupToggleBackgroundColorTest()
    {
        this->setupApplicationCameraClearColor();
        this->loadCLIScript();
    }
    void tearToggleBackgroundColorTestDown()
    {
        this->tearApplicationCameraClearColorDown();
    }
