
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

#ifndef LUA_CROSS_PLATFORM_EXAMPLES_RESOURCE_H
#define LUA_CROSS_PLATFORM_EXAMPLES_RESOURCE_H

// Pool+loadResource Start
#include <fstream>

// Pool+loadResource End
// ResourceStreamBuffer Start
#include <iostream>

// ResourceStreamBuffer End

// RESOURCE_LOG Start
#include "log.h"
#include "format.h"
#define RESOURCE_LOG_PREFIX "resource %s"
#define RESOURCE_LOG(...) \
    log::logprintf( \
        RESOURCE_LOG_PREFIX, \
        format::printfString(__VA_ARGS__).c_str() \
    )

// RESOURCE_LOG End
// RESOURCE_POOL_LOG Start
#include "log.h"
#include "format.h"
#define RESOURCE_POOL_LOG_PREFIX "resource::Pool(%p) %s"
#define RESOURCE_POOL_LOG(...) \
    log::logprintf( \
        RESOURCE_POOL_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
// RESOURCE_POOL_LOG End

namespace lcpe
{
namespace resource
{

// Resource Start
//! Resource container.
struct Resource
{
    Resource(
        const std::string &group,
        const std::string &name,
        const std::string &contents,
        unsigned int len
    ) :
        group(group),
        name(name),
        contents(contents),
        len(len)
    { }

    std::string group;
    std::string name;
    std::string contents;
    unsigned int len;
};
// Resource End
// ResourceStreamBuffer Start
//! Work with Resource contents as with any stream.
struct ResourceStreamBuffer : std::streambuf
{
    ResourceStreamBuffer(const Resource &resource)
    {
        char *contents = const_cast<char *>(resource.contents.data());
        this->setg(contents, contents, contents + resource.len);
    }
    // Implement 'seekoff()' to support 'seekg()' calls.
    // OpenSceneGraph plugins like OSG and ImageIO use 'seekg()'.
    // Topic: How to implement custom std::streambuf's seekoff()?
    // Source: https://stackoverflow.com/a/46068920
    std::streampos seekoff(
        std::streamoff off,
        std::ios_base::seekdir dir,
        std::ios_base::openmode which = std::ios_base::in
    ) {
        if (dir == std::ios_base::cur)
            this->gbump(off);
        else if (dir == std::ios_base::end)
            this->setg(this->eback(), this->egptr() + off, this->egptr());
        else if (dir == std::ios_base::beg)
            this->setg(this->eback(), this->eback() + off, this->egptr());
        return this->gptr() - this->eback();
    }
};
// ResourceStreamBuffer End

// extension Start
std::string extension(const Resource &resource)
{
    auto dotPosition = resource.name.rfind(".");
    // Return empty extension if we cannot detect it.
    if (dotPosition == std::string::npos)
    {
        RESOURCE_LOG(
            "ERROR Could not detect file extension for '%s/%s' resource",
            resource.group.c_str(),
            resource.name.c_str()
        );
        return "";
    }
    return resource.name.substr(dotPosition + 1);
}
// extension End


// Pool Start
class Pool
{
    public:
        Pool() { }

        std::vector<Resource> resources;

        void addResource(Resource &resource)
        {
            this->resources.push_back(resource);
        }

        Resource *resource(const std::string &group, const std::string &name)
        {
            auto count = this->resources.size();
            for (int i = 0; i < count; ++i)
            {
                Resource *res = &this->resources[i];
                if (
                    (res->group == group) &&
                    (res->name == name)
                ) {
                    return res;
                }
            }

            return 0;
        }

// Pool End
        // Pool+loadResource Start
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
        // Pool+loadResource End
// Pool Start
};
// Pool End

} // namespace resource
} // namespace lcpe

#endif // LUA_CROSS_PLATFORM_EXAMPLES_RESOURCE_H

