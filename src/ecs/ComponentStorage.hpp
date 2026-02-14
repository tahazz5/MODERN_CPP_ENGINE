#pragma once

#include "SparseSet.hpp"

namespace engine {

class ComponentStorage {
public:
    template<typename Component>
    void add(EntityID id, const Component& comp);

    template<typename Component>
    void remove(EntityID id);

    template<typename Component>
    Component* get(EntityID id);
};

} // namespace engine
