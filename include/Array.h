#ifndef CPP_CONTAINERS_ARRAY_H
#define CPP_CONTAINERS_ARRAY_H
#include <algorithm>
#include <complex>

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
};

#endif //CPP_CONTAINERS_ARRAY_H
