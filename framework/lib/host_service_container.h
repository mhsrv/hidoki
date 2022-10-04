#pragma once
#include <scope.h>
#include <interface/service_collection.h>
namespace hidoki {
    struct host_service_container final : public utils::service_collection {
    public:
        ~host_service_container();

        std::unique_ptr<scope> create_scope();

        template <typename TRegister, typename TService>
        void add_scoped(TService *service(utils::service_provider *))
        {
            auto obj = new std::function([service](utils::service_provider * scope) {
                return reinterpret_cast<void*>(dynamic_cast<TRegister*>(service(scope)));
            });

            register_finalizer_scoped(obj, [obj]() {
                delete obj;
            });

            register_type_scoped(typeid(TRegister).hash_code(), obj);
        }

        template <typename TService>
        void add_scoped()
        {
            return add_scoped<TService, TService>();
        }

        template <typename TRegister, typename TService>
        void add_scoped()
        {
            auto obj = new std::function([](utils::service_provider * scope) {
                return reinterpret_cast<void*>(dynamic_cast<TRegister*>(scope->construct<TService>()));
            });

            register_finalizer_scoped(obj, [obj]() {
                delete obj;
            });

            register_type_scoped(typeid(TRegister).hash_code(), obj);
        }

        template <typename TService>
        void add_scoped(TService *service(utils::service_provider *))
        {
            return add_scoped<TService, TService>(service);
        }

        std::vector<void*> get_all(size_t id) final;

    protected:

        void register_type_scoped(size_t id, scoped_service *service);

        void register_finalizer_scoped(scoped_service *service, const std::function<void()>& finalizer);

        void register_type(size_t id, void* service) final;

        void register_finalizer(void* service, const std::function<void()>& finalizer) final;

        void remove(size_t id, void* service) final;

    private:
        std::unordered_map<size_t, std::vector<void*>> m_types {};
        std::unordered_map<void*, std::function<void()>> m_finalizers {};

        scoped_map m_scoped_types {};
        std::unordered_map<scoped_service*, std::function<void()>> m_scoped_finalizers {};

    };

}