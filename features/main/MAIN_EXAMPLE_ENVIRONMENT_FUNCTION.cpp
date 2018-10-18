FEATURE main.h/Impl
#define MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(NAME) \
    std::vector<std::string> NAME ( \
        const std::string &key, \
        const std::vector<std::string> &values \
    )
