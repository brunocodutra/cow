// MIT License
// 
// Copyright (c) 2018 Bruno Dutra
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef COW_HPP
#define COW_HPP
#ifndef COW_UNBOX_HPP
#define COW_UNBOX_HPP
#ifndef COW_VALUE_HPP
#define COW_VALUE_HPP
#ifndef COW_DETAIL_TRAITS_HPP
#define COW_DETAIL_TRAITS_HPP
#include <type_traits>
namespace cow::detail {
    template<typename to>
    void convert(to);
    template<typename To,
        typename... From,
        typename = decltype(convert<To>({std::declval<From>()...})),
        bool disabled = std::is_array_v<To> || std::is_function_v<To>>
    std::true_type is_convertible_impl(std::enable_if_t<!disabled, int>);
    template<typename, typename...>
    std::false_type is_convertible_impl(...);
    template<typename To, typename... From>
    struct is_convertible : decltype(is_convertible_impl<To, From...>(0)) {};
    template<typename To, typename From>
    struct is_convertible<To, From> : std::is_convertible<From, To> {};
    template<typename To, typename... From>
    constexpr bool is_convertible_v = is_convertible<To, From...>::value;
}
#endif
#include <cassert>
#include <memory>
#include <type_traits>
#include <utility>
namespace cow::detail {
    template<typename T,
        bool move = is_convertible_v<T, std::decay_t<T>&&>,
        bool copy = is_convertible_v<T, std::decay_t<T> const&>>
    struct value;
    template<typename T>
    struct is_value : std::false_type {};
    template<typename T>
    struct is_value<value<T>> : std::true_type {};
    template<typename T>
    constexpr bool is_value_v = is_value<T>::value;
    template<typename V, typename R = decltype(std::declval<V&&>().get())>
    using value_type_t = std::enable_if_t<is_value_v<std::decay_t<V>>, R>;
    template<typename T>
    class value_base;
    template<typename T>
    class value_base<T const> {
        static_assert(std::is_copy_constructible_v<T>);
        std::shared_ptr<T const> ptr;
        template<typename... Us>
        static auto make(Us&&... us) {
            return std::make_shared<T const>(std::forward<Us>(us)...);
        }
        template<typename U>
        friend class value_base;
    public:
        value_base(value_base&&) = default;
        value_base(value_base const&) = default;
        template<typename... Us,
            bool unary = sizeof...(Us) == 1,
            bool viable = is_convertible_v<T, Us&&...>,
            std::enable_if_t<!unary && viable, int> = 0>
        value_base(Us&&... us) : ptr(make(std::forward<Us>(us)...)) {}
        template<typename... Us,
            bool unary = sizeof...(Us) == 1,
            bool implicit = is_convertible_v<T, Us&&...>,
            bool viable = std::is_constructible_v<T, Us&&...>,
            std::enable_if_t<!unary && !implicit && viable, int> = 0>
        explicit value_base(Us&&... us) : ptr(make(std::forward<Us>(us)...)) {}
        template<typename U,
            bool disabled = is_value_v<std::decay_t<U>>,
            bool viable = is_convertible_v<T, U&&>,
            std::enable_if_t<!disabled && viable, int> = 0>
        value_base(U&& u) : ptr(make(std::forward<U>(u))) {}
        template<typename U,
            bool disabled = is_value_v<std::decay_t<U>>,
            bool implicit = is_convertible_v<T, U&&>,
            bool viable = std::is_constructible_v<T, U&&>,
            std::enable_if_t<!disabled && !implicit && viable, int> = 0>
        explicit value_base(U&& u) : ptr(make(std::forward<U>(u))) {}
        template<typename V,
            typename U = value_type_t<V&&>,
            bool aliasable = is_convertible_v<T const*, std::decay_t<U>*>,
            bool viable = is_convertible_v<T, U&&>,
            std::enable_if_t<viable, int> = 0>
        value_base(V&& v) noexcept(aliasable) {
            if constexpr(aliasable) {
                ptr = std::forward<V>(v).ptr;
            } else {
                ptr = make(std::forward<V>(v).get());
            }
        }
        template<typename V,
            typename U = value_type_t<V&&>,
            bool aliasable = is_convertible_v<T const*, std::decay_t<U>*>,
            bool implicit = is_convertible_v<T, U&&>,
            bool viable = std::is_constructible_v<T, U&&>,
            std::enable_if_t<!implicit && viable, int> = 0>
        explicit value_base(V&& v) noexcept(aliasable) {
            if constexpr(aliasable) {
                ptr = std::forward<V>(v).ptr;
            } else {
                ptr = make(std::forward<V>(v).get());
            }
        }
        T const& get() const& noexcept {
            return *ptr;
        }
        T const&& get() const&& noexcept {
            return std::move(get());
        }
        auto operator-> () const noexcept {
            return ptr;
        }
        operator T const&() const noexcept {
            return get();
        }
        template<typename U,
            bool aliasable = is_convertible_v<U const*, T*>,
            std::enable_if_t<aliasable, int> = 0>
        operator U const&() const noexcept {
            return get();
        }
    };
    template<typename T>
    class value_base : public value_base<T const> {
        using base = value_base<T const>;
    public:
        using base::base;
        using base::get;
        value_base(value_base&&) = default;
        value_base(value_base const&) = default;
        value_base& operator=(value_base other) noexcept {
            base::ptr = std::move(other).ptr;
            return *this;
        }
        template<typename U,
            bool assignable = std::is_assignable_v<T&, U&&>,
            bool disabled = !assignable || is_value_v<std::decay_t<U>>,
            bool viable = std::is_constructible_v<value_base, U&&>,
            bool nothrow = std::is_nothrow_constructible_v<value_base, U&&>,
            std::enable_if_t<!disabled && viable, int> = 0>
        value_base& operator=(U&& u) noexcept(nothrow) {
            return *this = value_base(std::forward<U>(u));
        }
        template<typename V,
            bool disabled = !std::is_assignable_v<T&, value_type_t<V&&>&&>,
            bool viable = std::is_constructible_v<value_base, V&&>,
            bool nothrow = std::is_nothrow_constructible_v<value_base, V&&>,
            std::enable_if_t<!disabled && viable, int> = 0>
        value_base& operator=(V&& v) noexcept(nothrow) {
            return *this = value_base(std::forward<V>(v));
        }
        T& get() & {
            if(base::ptr.use_count() > 1) {
                base::ptr = base::make(*base::ptr);
            }
            assert(base::ptr.use_count() == 1);
            return const_cast<T&>(*base::ptr);
        }
        T&& get() && {
            return std::move(get());
        }
    };
    template<typename T>
    struct value<T, false, false> : value_base<T> {
        using value_base<T>::value_base;
        using value_base<T>::operator=;
        explicit value(value&&) = default;
        explicit value(value const&) = default;
        value& operator=(value&&) = default;
        value& operator=(value const&) = default;
    };
    template<typename T>
    struct value<T, true, false> : value_base<T> {
        using value_base<T>::value_base;
        using value_base<T>::operator=;
        value(value&&) = default;
        explicit value(value const&) = default;
        value& operator=(value&&) = default;
        value& operator=(value const&) = default;
    };
    template<typename T>
    struct value<T, false, true> : value_base<T> {
        using value_base<T>::value_base;
        using value_base<T>::operator=;
        explicit value(value&&) = default;
        value(value const&) = default;
        value& operator=(value&&) = default;
        value& operator=(value const&) = default;
    };
    template<typename T>
    struct value<T, true, true> : value_base<T> {
        using value_base<T>::value_base;
        using value_base<T>::operator=;
        value(value&&) = default;
        value(value const&) = default;
        value& operator=(value&&) = default;
        value& operator=(value const&) = default;
    };
    template<typename T>
    value(T)->value<T>;
    template<typename T>
    value(value<T>)->value<T>;
}
namespace cow {
    using detail::value;
}
#endif
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
#ifndef COW_VERSION_HPP
#define COW_VERSION_HPP
#define COW_MAJOR 0
#define COW_MINOR 1
#define COW_PATCH 0
#define COW_SEMVER(MAJOR, MINOR, PATCH) (((MAJOR)*1000000) + ((MINOR)*10000) + (PATCH))
#define COW_VERSION COW_SEMVER(COW_MAJOR, COW_MINOR, COW_PATCH)
#endif
#endif
