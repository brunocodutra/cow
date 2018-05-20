#ifndef COW_VALUE_HPP
#define COW_VALUE_HPP

#include "detail/traits.hpp"

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

    template<typename V>
    using value_type_t = decltype(std::declval<V&&>().get());

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
