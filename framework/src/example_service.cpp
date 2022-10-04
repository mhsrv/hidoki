#include <example_service.h>
#include <iostream>
void hidoki::example_service::something() {
    std::cout << "Hello, World!" << std::endl;
}

hidoki::example_service *hidoki::example_service::make() {
    return new example_service{};
}
