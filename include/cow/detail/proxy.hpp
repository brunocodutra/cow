#ifndef COW_DETAIL_PROXY_HPP
#define COW_DETAIL_PROXY_HPP

#include <memory>
#include <type_traits>
#include <utility>

namespace cow::detail {

    template<typename T, typename = void>
    class proxy : public std::shared_ptr<T> {
        using base = std::shared_ptr<T>;

    public:
        proxy(proxy&&) = default;
        proxy(proxy const&) = default;

        proxy(base&& b) : base(std::move(b)){};
        proxy(base const& b) : base(b){};

        template<typename... Us>
        explicit proxy(Us&&... us)
            : base(std::make_shared<T>(std::forward<Us>(us)...)) {}

        proxy& operator=(proxy&&) = default;
        proxy& operator=(proxy const&) = default;

        proxy& operator=(base&& b) {
            base::operator=(std::move(b));
            return *this;
        };

        proxy& operator=(base const& b) {
            base::operator=(b);
            return *this;
        };

        using base::operator*;
        using base::operator->;

        bool aliased() const noexcept {
            return base::use_count() > 1;
        }
    };

    template<typename T,
        bool trivial = std::is_trivially_copy_constructible_v<T>,
        bool small = sizeof(T) <= sizeof(std::shared_ptr<T>)>
    constexpr bool is_embeddable_v = trivial and small;

    template<typename T>
    class proxy<T, std::enable_if_t<is_embeddable_v<T>>> {
        std::aligned_storage_t<sizeof(std::shared_ptr<T>), alignof(T)> data;

    public:
        proxy(proxy&&) = default;
        proxy(proxy const&) = default;

        template<typename... Us,
            bool nothrow = std::is_nothrow_constructible_v<T, Us&&...>>
        explicit proxy(Us&&... us) noexcept(nothrow) {
            new(&data) std::decay_t<T>(std::forward<Us>(us)...);
        }

        ~proxy() noexcept(std::is_nothrow_destructible_v<T>) {
            (*this)->~T();
        }

        proxy& operator=(proxy&&) = default;
        proxy& operator=(proxy const&) = default;

        T& operator*() noexcept {
            return *reinterpret_cast<T*>(&data);
        }

        T const& operator*() const noexcept {
            return *reinterpret_cast<T const*>(&data);
        }

        T* operator->() noexcept {
            return std::addressof(**this);
        }

        T const* operator->() const noexcept {
            return std::addressof(**this);
        }

        bool aliased() const noexcept {
            return false;
        }
    };
}

#endif
