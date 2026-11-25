#ifndef CPP_CONTAINERS_ARRAY_H
#define CPP_CONTAINERS_ARRAY_H
#include <algorithm>

template <typename T, std::size_t N>
class Array {
private:
    T elems[N]{};

public:
    constexpr Array() noexcept = default;

    template <typename... Args>
    requires (sizeof...(Args) > 0) &&
             (sizeof...(Args) <= N) &&
             (std::convertible_to<Args, T> && ...)
    constexpr Array(Args&&... args) : elems{std::forward<Args>(args)...} {}

    [[nodiscard]] constexpr bool empty() const noexcept {
        return N == 0;
    }

     [[nodiscard]] constexpr size_t size() const noexcept {
        return N;
    }

    constexpr T& operator[](size_t index) {
        return elems[index];
    }

    constexpr const T& operator[](size_t index) const {
        return elems[index];
    }

    template<std::ptrdiff_t Index>
        requires(Index >= 0) && (Index < static_cast<std::ptrdiff_t>(N))
    constexpr T& get() {
        return elems[Index];
    }

    template<std::ptrdiff_t Index>
        requires(Index >= 0) && (Index < static_cast<std::ptrdiff_t>(N))
    constexpr const T& get() const {
        return elems[Index];
    }
};

#endif //CPP_CONTAINERS_ARRAY_H
