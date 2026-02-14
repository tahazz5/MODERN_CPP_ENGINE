#pragma once

#include "Entity.hpp"
#include "SparseSet.hpp"

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace engine {

class ComponentStorage {
public:
    template<typename Component>
    void add(EntityID id, const Component& comp) {
        auto& storage = getOrCreate<Component>();
        storage.components.insert(id, comp);
    }

    template<typename Component>
    void remove(EntityID id) {
        if (auto* storage = getIfExists<Component>()) {
            storage->components.remove(id);
        }
    }

    template<typename Component>
    Component* get(EntityID id) {
        auto* storage = getIfExists<Component>();
        if (storage == nullptr) {
            return nullptr;
        }
        return storage->components.get(id);
    }

private:
    struct IStorage {
        virtual ~IStorage() = default;
    };

    template<typename Component>
    struct Storage final : IStorage {
        SparseSet<Component> components;
    };

    template<typename Component>
    Storage<Component>& getOrCreate() {
        const auto key = std::type_index(typeid(Component));
        auto it = storages_.find(key);
        if (it == storages_.end()) {
            auto storage = std::make_unique<Storage<Component>>();
            auto* raw = storage.get();
            storages_.emplace(key, std::move(storage));
            return *raw;
        }
        return *static_cast<Storage<Component>*>(it->second.get());
    }

    template<typename Component>
    Storage<Component>* getIfExists() {
        const auto key = std::type_index(typeid(Component));
        auto it = storages_.find(key);
        if (it == storages_.end()) {
            return nullptr;
        }
        return static_cast<Storage<Component>*>(it->second.get());
    }

    std::unordered_map<std::type_index, std::unique_ptr<IStorage>> storages_;
};

} // namespace engine
