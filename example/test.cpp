#include <example_service.h>
#include <service_container.h>

int fn(hidoki::example *example) {
    example->something();
    return 0;
}

int main() {
    utils::service_container services{};
    services.add<hidoki::example, hidoki::example_service>();
    return services.inject(fn);
}