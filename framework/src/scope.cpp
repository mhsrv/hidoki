#include <scope.h>
#include <host_service_container.h>

hidoki::scope::scope(hidoki::host_service_container *parent, hidoki::scoped_map &map) : m_scoped_services(map), m_parent(parent)
{

}

std::vector<void *> hidoki::scope::get_all(size_t id) {
    std::vector<void *> result{};


    if (!m_cache.contains(id)) {
        if (m_scoped_services.contains(id)) {
            for (auto& fn : m_scoped_services[id]) {
                auto service = fn->operator()(this);
                m_finalizers.emplace_back([service]{
                    operator delete(service);
                });
                result.push_back(service);
            }
        }
        m_cache.insert({id, result});
    } else {
        for(auto& service : m_cache[id]) {
            result.push_back(service);
        }
    }

    for (auto& service : m_parent->get_all(id)) {
        result.push_back(service);
    }

    return result;
}

hidoki::scope::~scope() {
    for(const auto& finalizer : m_finalizers) {
        finalizer();
    }
}
