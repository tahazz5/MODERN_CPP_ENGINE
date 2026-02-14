#pragma once

#include <cstdint>
#include <limits>
#include <vector>

namespace engine {

template<typename T>
class SparseSet {
public:
    void insert(std::uint32_t id, const T& value) {
        ensureSparseSize(id);
        if (contains(id)) {
            dense_[sparse_[id]] = value;
            return;
        }

        sparse_[id] = static_cast<std::uint32_t>(dense_.size());
        entities_.push_back(id);
        dense_.push_back(value);
    }

    void remove(std::uint32_t id) {
        if (!contains(id)) {
            return;
        }

        const std::uint32_t removeIndex = sparse_[id];
        const std::uint32_t lastIndex = static_cast<std::uint32_t>(dense_.size() - 1);

        if (removeIndex != lastIndex) {
            dense_[removeIndex] = dense_[lastIndex];
            const std::uint32_t movedEntity = entities_[lastIndex];
            entities_[removeIndex] = movedEntity;
            sparse_[movedEntity] = removeIndex;
        }

        dense_.pop_back();
        entities_.pop_back();
        sparse_[id] = invalidIndex();
    }

    T* get(std::uint32_t id) {
        if (!contains(id)) {
            return nullptr;
        }
        return &dense_[sparse_[id]];
    }

    const T* get(std::uint32_t id) const {
        if (!contains(id)) {
            return nullptr;
        }
        return &dense_[sparse_[id]];
    }

    bool contains(std::uint32_t id) const {
        if (id >= sparse_.size()) {
            return false;
        }
        const std::uint32_t idx = sparse_[id];
        return idx != invalidIndex() && idx < dense_.size() && entities_[idx] == id;
    }

    std::size_t size() const noexcept {
        return dense_.size();
    }

private:
    static constexpr std::uint32_t invalidIndex() {
        return std::numeric_limits<std::uint32_t>::max();
    }

    void ensureSparseSize(std::uint32_t id) {
        if (id >= sparse_.size()) {
            sparse_.resize(static_cast<std::size_t>(id) + 1, invalidIndex());
        }
    }

    std::vector<T> dense_;
    std::vector<std::uint32_t> entities_;
    std::vector<std::uint32_t> sparse_;
};

} // namespace engine
