#include <host_service_container.h>

hidoki::host_service_container::~host_service_container() {
    for (auto& finalizer : m_finalizers) {
        finalizer.second();
    }
    for (auto& finalizer : m_scoped_finalizers) {
        finalizer.second();
    }
}

std::unique_ptr<hidoki::scope> hidoki::host_service_container::create_scope() {
    return std::make_unique<scope>(this, m_scoped_types);
}

std::vector<void *> hidoki::host_service_container::get_all(size_t id) {
    if (!m_types.contains(id)) {
        return {};
    }
    return m_types[id];
}

void hidoki::host_service_container::register_type_scoped(size_t id, hidoki::scoped_service *service) {
    if (!m_scoped_types.contains(id)) {
        m_scoped_types.insert({ id, {} });
    }
    m_scoped_types[id].push_back(service);
}

void hidoki::host_service_container::register_finalizer_scoped(hidoki::scoped_service *service,
                                                               const std::function<void()> &finalizer) {
    m_scoped_finalizers.insert({ service, finalizer });
}

void hidoki::host_service_container::register_type(size_t id, void *service) {
    if (!m_types.contains(id)) {
        m_types.insert({ id, {} });
    }
    m_types[id].push_back(service);
}

void hidoki::host_service_container::register_finalizer(void *service, const std::function<void()> &finalizer) {
    m_finalizers.insert({ service, finalizer });
}

void hidoki::host_service_container::remove(size_t id, void *service) {
    auto types = get_all(id);
    if (types.empty() || std::erase(m_types[id], service) == 0) {
        return;
    }

    if (m_types[id].empty()) {
        m_types.erase(id);
    }

    if (m_finalizers.contains(service)) {
        m_finalizers[service]();
        m_finalizers.erase(service);
    }
}
