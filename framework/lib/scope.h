#pragma once
#include <interface/service_provider.h>

namespace hidoki {
    using scoped_service = std::function<void*(utils::service_provider *services)>;
    using scoped_map = std::unordered_map<size_t, std::vector<scoped_service*>>;
    struct host_service_container;

    struct scope final : public utils::service_provider {
        ~scope();
        scope(host_service_container* parent, scoped_map &map);
    protected:
        std::vector<void*> get_all(size_t id) final;;
    private:
        scoped_map &m_scoped_services;
        host_service_container *m_parent;
        std::unordered_map<size_t, std::vector<void *>> m_cache{};
        std::vector<std::function<void()>> m_finalizers {};
    };
}