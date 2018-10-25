FEATURE resource.h/Include
#include <fstream>

FEATURE resource.h/Impl
public:
    std::vector<std::string> locations;

    void loadResource(
        const std::string &group,
        const std::string &name
    ) { 
        // NOTE We only load local resources at the moment.
        // TODO Load remote resources.

        for (auto location : this->locations)
        {
            auto fileName = location + "/" + name;
            std::ifstream localResource(fileName);
            if (localResource)
            {
                // Read file contents into string.
                std::string fileContents(
                    (std::istreambuf_iterator<char>(localResource)),
                    (std::istreambuf_iterator<char>())
                );
                resource::Resource res(
                    group,
                    name,
                    fileContents,
                    fileContents.length()
                );
                // Add resource.
                this->addResource(res);
                // Stop checking other locations.
                return;
            }
        }

        RESOURCE_POOL_LOG(
            "ERROR Could not find resource '%s/%s' at any "
            "of the specified locations",
            group.c_str(),
            name.c_str()
        );
    }
