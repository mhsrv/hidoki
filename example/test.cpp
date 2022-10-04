#include <example_service.h>
#include "host.h"

// todo: add a web-server service
// todo: add a connection handler service

// todo: add a HTTP request handler service (this service will create a scope that gets used by the middleware and the routes)
// todo: add a middleware container service
// todo: add a routing service
// todo: add a way to add routes to the routing service (that are classes that implement an interface or are functions)

// todo: split the files into multiple statically linked libraries that contain one interface implementation each (called modules)
// todo: create a dynamic library that contains all those static libraries

// todo: create a static method that creates that service container with the required services already injected
// todo: create a CLI tool that creates CMake projects (statically or dynamically linked - specified by the user) that use hidoki
// todo: add the following options to it:
//        - init <static/dynamic> [folder = pwd] (creates a cmake project)
//        - build (build the library/executable)
//        - <path to library> (loads a library and runs it)
//        - serve (builds and runs this project)
//        - remove <module> (remove a module from the project)
//        - install <dependency/module> (add a new dependency to the project)
//        - generate (generates a .cmake file that builds a custom static library from the enabled modules and installed dependencies)
//       store the enabled modules, dependencies, the name of the project, etc.. in a json file
//

int main() {
    auto webhost = hidoki::host::create();
    webhost->services().add_scoped<hidoki::example, hidoki::example_service>();
    auto scope = webhost->services().create_scope();
    return 0;
}