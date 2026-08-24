#ifndef CPP_CONTAINERS_VECTOR_H
#define CPP_CONTAINERS_VECTOR_H
#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <bits/stl_uninitialized.h>

template<typename T>
class Vector {
private:
    T* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
public:
    Vector() noexcept = default;

    Vector(std::initializer_list<T> il) {
        if (il.size() == 0) return;

        data_ = static_cast<T*>(::operator new(il.size() * sizeof(T)));

        try {
            std::uninitialized_copy_n(il.begin(), il.size(), data_);
        } catch (...) {
            ::operator delete(data_);
            throw;
        }

        size_ = il.size();
        capacity_ = size_;
    }

    T& operator[](std::size_t index) noexcept;
    const T& operator[](std::size_t index) const noexcept;

    [[nodiscard]] std::size_t Size() const noexcept {
        return size_;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }
};

template<typename T>
T& Vector<T>::operator[](std::size_t index) noexcept {
    return data_[index];
}

template<typename T>
const T& Vector<T>::operator[](std::size_t index) const noexcept {
    return data_[index];
}

#endif //CPP_CONTAINERS_VECTOR_H
