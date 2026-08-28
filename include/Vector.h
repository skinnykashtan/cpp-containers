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

    T& back() noexcept {
        return data_[size_-1];
    }

    const T& back() const noexcept {
        return data_[size_-1];
    }

    void ReAlloc(std::size_t newCapacity);

    void PushBack(const T& value);
    void PushBack(T&& value);

    void PopBack() noexcept;
};

template<typename T>
void Vector<T>::ReAlloc(std::size_t newCapacity) {
    if (newCapacity <= capacity_) return;

    T* newBlock = static_cast<T*>(::operator new(newCapacity * sizeof(T)));

    if constexpr (std::is_nothrow_move_constructible_v<T>) {
        std::uninitialized_move_n(data_, size_, newBlock);
    } else {
        try {
            std::uninitialized_copy_n(data_, size_, newBlock);
        } catch (...) {
            ::operator delete(newBlock);
            throw;
        }
    }

    for (std::size_t i = 0; i < size_; i++) {
        std::destroy_at(data_ + i);
    }

    ::operator delete(data_);

    data_ = newBlock;
    capacity_ = newCapacity;
}

template<typename T>
void Vector<T>::PushBack(const T& value) {
    if (size_ == capacity_) {
        std::size_t newCapacity = capacity_ == 0 ? 2 : capacity_ + capacity_ / 2;
        ReAlloc(newCapacity);
    }

    ::new(data_ + size_) T(value);
    ++size_;
}

template<typename T>
void Vector<T>::PushBack(T&& value) {
    if (size_ == capacity_) {
        std::size_t newCapacity = capacity_ == 0 ? 2 : capacity_ + capacity_ / 2;
        ReAlloc(newCapacity);
    }

    ::new(data_ + size_) T(std::move(value));
    ++size_;
}

template<typename T>
void Vector<T>::PopBack() noexcept {
    if (this->empty()) return;

    std::destroy_at(data_ + size_ - 1);
    --size_;
}

template<typename T>
T& Vector<T>::operator[](std::size_t index) noexcept {
    return data_[index];
}

template<typename T>
const T& Vector<T>::operator[](std::size_t index) const noexcept {
    return data_[index];
}

#endif //CPP_CONTAINERS_VECTOR_H
