#pragma once

#include <host_service_container.h>

namespace hidoki {
    struct host {
        host_service_container& services();
        static std::unique_ptr<host> create();
    private:
        host_service_container m_services{};
    };

}
