#include <host.h>

hidoki::host_service_container &hidoki::host::services() {
    return m_services;
}

std::unique_ptr<hidoki::host> hidoki::host::create() {
    auto host = std::make_unique<hidoki::host>();
    host->services().add(&host);
    host->services().add<utils::service_provider>(&host->services());
    host->services().add<utils::service_collection>(&host->services());
    return host;
}
