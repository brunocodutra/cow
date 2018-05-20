#ifndef COW_UNBOX_HPP
#define COW_UNBOX_HPP

#include "value.hpp"

#include <functional>
#include <type_traits>
#include <utility>

namespace cow {
    // clang-format off

    template<typename T, typename F,
        std::enable_if_t<!std::is_invocable_v<F&&, T const&>, int> = 0>
    decltype(auto) unbox(value<T>& val, F&& f) {
        return std::invoke(std::forward<F>(f), val.get());
    }

    template<typename T, typename F,
        std::enable_if_t<!std::is_invocable_v<F&&, T const&&>, int> = 0>
    decltype(auto) unbox(value<T>&& val, F&& f) {
        return std::invoke(std::forward<F>(f), std::move(val).get());
    }

    template<typename T, typename F,
        bool nothrow = std::is_nothrow_invocable_v<F&&, T const&>>
    decltype(auto) unbox(value<T> const& val, F&& f) noexcept(nothrow) {
        return std::invoke(std::forward<F>(f), val.get());
    }

    template<typename T, typename F,
        bool nothrow = std::is_nothrow_invocable_v<F&&, T const&&>>
    decltype(auto) unbox(value<T> const&& val, F&& f) noexcept(nothrow) {
        return std::invoke(std::forward<F>(f), std::move(val).get());
    }

    // clang-format on
}

#endif
