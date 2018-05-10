#ifndef TEST_HPP
#define TEST_HPP

#include <cassert>

enum class qualifier {
    lref,
    clref,
    rref,
    crref
};

struct base {
    int gen = 0;

    explicit base() = default;
    explicit base(base&&) = default;

    explicit base(base const& other)
        : gen(other.gen + 1)
    {};

    base& operator=(base&&) = default;

    base& operator=(base const& other) {
        return *this = base(other);
    }

    explicit operator qualifier() & {
        return qualifier::lref;
    }

    explicit operator qualifier() && {
        return qualifier::rref;
    }

    explicit operator qualifier() const& {
        return qualifier::clref;
    }

    explicit operator qualifier() const&& {
        return qualifier::crref;
    }
};

struct derived : base {
    derived() = default;
    derived(derived &&) = default;
    derived(derived const&) = default;
    derived(base&& b) : base(std::move(b)) {}

    derived& operator=(derived&&) = default;
    derived& operator=(derived const&) = default;

    operator qualifier() & {
        return qualifier::lref;
    }

    operator qualifier() && {
        return qualifier::rref;
    }

    operator qualifier() const& {
        return qualifier::clref;
    }

    operator qualifier() const&& {
        return qualifier::crref;
    }
};

template<typename T, typename U>
T cast(U&& u) {
    return std::forward<U>(u);
}

template<typename T, typename... Args>
T make(Args&&... args) {
    return T(std::forward<Args>(args)...);
}

template<typename T>
T& lvalue(T&& val) {
    return val;
}

#define CHECK(...) assert((__VA_ARGS__))

#endif
