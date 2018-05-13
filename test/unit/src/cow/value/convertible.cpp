#include <cow.hpp>
#include <test.hpp>

int main() {

    /* Copy & Move */ {
        CHECK(std::is_convertible_v<base, cow::value<base>> == std::is_convertible_v<base, base>);
        CHECK(std::is_convertible_v<base&, cow::value<base>> == std::is_convertible_v<base&, base>);

        CHECK(std::is_convertible_v<base const, cow::value<base>> == std::is_convertible_v<base const, base>);
        CHECK(std::is_convertible_v<base const&, cow::value<base>> == std::is_convertible_v<base const&, base>);

        CHECK(std::is_convertible_v<base, cow::value<base const>> == std::is_convertible_v<base, base const>);
        CHECK(std::is_convertible_v<base&, cow::value<base const>> == std::is_convertible_v<base&, base const>);

        CHECK(std::is_convertible_v<base const, cow::value<base const>> == std::is_convertible_v<base const, base const>);
        CHECK(std::is_convertible_v<base const&, cow::value<base const>> == std::is_convertible_v<base const&, base const>);

        CHECK(std::is_convertible_v<derived, cow::value<derived>> == std::is_convertible_v<derived, derived>);
        CHECK(std::is_convertible_v<derived&, cow::value<derived>> == std::is_convertible_v<derived&, derived>);
        CHECK(cast<cow::value<derived>>(make<derived>())->gen == 0);
        CHECK(cast<cow::value<derived>>(lvalue(make<derived>()))->gen == 1);

        CHECK(std::is_convertible_v<derived const, cow::value<derived>> == std::is_convertible_v<derived const, derived>);
        CHECK(std::is_convertible_v<derived const&, cow::value<derived>> == std::is_convertible_v<derived const&, derived>);
        CHECK(cast<cow::value<derived>>(make<derived const>())->gen == 1);
        CHECK(cast<cow::value<derived>>(lvalue(make<derived const>()))->gen == 1);

        CHECK(std::is_convertible_v<derived, cow::value<derived const>> == std::is_convertible_v<derived, derived const>);
        CHECK(std::is_convertible_v<derived&, cow::value<derived const>> == std::is_convertible_v<derived&, derived const>);
        CHECK(cast<cow::value<derived const>>(make<derived>())->gen == 0);
        CHECK(cast<cow::value<derived const>>(lvalue(make<derived>()))->gen == 1);

        CHECK(std::is_convertible_v<derived const, cow::value<derived const>> == std::is_convertible_v<derived const, derived const>);
        CHECK(std::is_convertible_v<derived const&, cow::value<derived const>> == std::is_convertible_v<derived const&, derived const>);
        CHECK(cast<cow::value<derived const>>(make<derived const>())->gen == 1);
        CHECK(cast<cow::value<derived const>>(lvalue(make<derived const>()))->gen == 1);

        CHECK(std::is_convertible_v<derived, cow::value<base>> == std::is_convertible_v<derived, base>);
        CHECK(std::is_convertible_v<derived&, cow::value<base>> == std::is_convertible_v<derived&, base>);

        CHECK(std::is_convertible_v<derived const, cow::value<base>> == std::is_convertible_v<derived const, base>);
        CHECK(std::is_convertible_v<derived const&, cow::value<base>> == std::is_convertible_v<derived const&, base>);

        CHECK(std::is_convertible_v<derived, cow::value<base const>> == std::is_convertible_v<derived, base const>);
        CHECK(std::is_convertible_v<derived&, cow::value<base const>> == std::is_convertible_v<derived&, base const>);

        CHECK(std::is_convertible_v<derived const, cow::value<base const>> == std::is_convertible_v<derived const, base const>);
        CHECK(std::is_convertible_v<derived const&, cow::value<base const>> == std::is_convertible_v<derived const&, base const>);
    }

    /* Forwarding */ {
        CHECK(std::is_convertible_v<base, cow::value<derived>> == std::is_convertible_v<base, derived>);
        CHECK(std::is_convertible_v<base&, cow::value<derived>> == std::is_convertible_v<base&, derived>);
        CHECK(cast<cow::value<derived>>(make<base>())->gen == 0);

        CHECK(std::is_convertible_v<base const, cow::value<derived>> == std::is_convertible_v<base const, derived>);
        CHECK(std::is_convertible_v<base const&, cow::value<derived>> == std::is_convertible_v<base const&, derived>);

        CHECK(std::is_convertible_v<base, cow::value<derived const>> == std::is_convertible_v<base, derived const>);
        CHECK(std::is_convertible_v<base&, cow::value<derived const>> == std::is_convertible_v<base&, derived const>);
        CHECK(cast<cow::value<derived const>>(make<base>())->gen == 0);

        CHECK(std::is_convertible_v<base const, cow::value<derived const>> == std::is_convertible_v<base const, derived const>);
        CHECK(std::is_convertible_v<base const&, cow::value<derived const>> == std::is_convertible_v<base const&, derived const>);

        CHECK(std::is_convertible_v<base, cow::value<qualifier>> == std::is_convertible_v<base, qualifier>);
        CHECK(std::is_convertible_v<base&, cow::value<qualifier>> == std::is_convertible_v<base&, qualifier>);

        CHECK(std::is_convertible_v<base const, cow::value<qualifier>> == std::is_convertible_v<base const, qualifier>);
        CHECK(std::is_convertible_v<base const&, cow::value<qualifier>> == std::is_convertible_v<base const&, qualifier>);

        CHECK(std::is_convertible_v<base, cow::value<qualifier const>> == std::is_convertible_v<base, qualifier const>);
        CHECK(std::is_convertible_v<base&, cow::value<qualifier const>> == std::is_convertible_v<base&, qualifier const>);

        CHECK(std::is_convertible_v<base const, cow::value<qualifier const>> == std::is_convertible_v<base const, qualifier const>);
        CHECK(std::is_convertible_v<base const&, cow::value<qualifier const>> == std::is_convertible_v<base const&, qualifier const>);

        CHECK(std::is_convertible_v<derived, cow::value<qualifier>> == std::is_convertible_v<derived, qualifier>);
        CHECK(std::is_convertible_v<derived&, cow::value<qualifier>> == std::is_convertible_v<derived&, qualifier>);
        CHECK(cast<cow::value<qualifier>>(make<cow::value<derived>>()) == qualifier::rref);
        CHECK(cast<cow::value<qualifier>>(lvalue(make<cow::value<derived>>())) == qualifier::lref);

        CHECK(std::is_convertible_v<derived const, cow::value<qualifier>> == std::is_convertible_v<derived const, qualifier>);
        CHECK(std::is_convertible_v<derived const&, cow::value<qualifier>> == std::is_convertible_v<derived const&, qualifier>);
        CHECK(cast<cow::value<qualifier>>(make<cow::value<derived> const>()) == qualifier::crref);
        CHECK(cast<cow::value<qualifier>>(lvalue(make<cow::value<derived> const>())) == qualifier::clref);

        CHECK(std::is_convertible_v<derived, cow::value<qualifier const>> == std::is_convertible_v<derived, qualifier const>);
        CHECK(std::is_convertible_v<derived&, cow::value<qualifier const>> == std::is_convertible_v<derived&, qualifier const>);
        CHECK(cast<cow::value<qualifier const>>(make<cow::value<derived>>()) == qualifier::rref);
        CHECK(cast<cow::value<qualifier const>>(lvalue(make<cow::value<derived>>())) == qualifier::lref);

        CHECK(std::is_convertible_v<derived const, cow::value<qualifier const>> == std::is_convertible_v<derived const, qualifier const>);
        CHECK(std::is_convertible_v<derived const&, cow::value<qualifier const>> == std::is_convertible_v<derived const&, qualifier const>);
        CHECK(cast<cow::value<qualifier const>>(make<cow::value<derived const>>()) == qualifier::crref);
        CHECK(cast<cow::value<qualifier const>>(lvalue(make<cow::value<derived const>>())) == qualifier::clref);
    }

    /* Aliasing */ {
        CHECK(std::is_convertible_v<cow::value<base>, cow::value<base>> == std::is_convertible_v<base, base>);
        CHECK(std::is_convertible_v<cow::value<base>&, cow::value<base>> == std::is_convertible_v<base&, base>);

        CHECK(std::is_convertible_v<cow::value<base> const, cow::value<base>> == std::is_convertible_v<base const, base>);
        CHECK(std::is_convertible_v<cow::value<base> const&, cow::value<base>> == std::is_convertible_v<base const&, base>);

        CHECK(std::is_convertible_v<cow::value<base const>, cow::value<base>> == std::is_convertible_v<base const, base>);
        CHECK(std::is_convertible_v<cow::value<base const>&, cow::value<base>> == std::is_convertible_v<base const&, base>);

        CHECK(std::is_convertible_v<cow::value<base const> const, cow::value<base>> == std::is_convertible_v<base const, base>);
        CHECK(std::is_convertible_v<cow::value<base const> const&, cow::value<base>> == std::is_convertible_v<base const&, base>);

        CHECK(std::is_convertible_v<cow::value<base>, cow::value<base const>> == std::is_convertible_v<base, base const>);
        CHECK(std::is_convertible_v<cow::value<base>&, cow::value<base const>> == std::is_convertible_v<base&, base const>);

        CHECK(std::is_convertible_v<cow::value<base> const, cow::value<base const>> == std::is_convertible_v<base const, base const>);
        CHECK(std::is_convertible_v<cow::value<base> const&, cow::value<base const>> == std::is_convertible_v<base const&, base const>);

        CHECK(std::is_convertible_v<cow::value<base const>, cow::value<base const>> == std::is_convertible_v<base const, base const>);
        CHECK(std::is_convertible_v<cow::value<base const>&, cow::value<base const>> == std::is_convertible_v<base const&, base const>);

        CHECK(std::is_convertible_v<cow::value<base const> const, cow::value<base const>> == std::is_convertible_v<base const, base const>);
        CHECK(std::is_convertible_v<cow::value<base const> const&, cow::value<base const>> == std::is_convertible_v<base const&, base const>);

        CHECK(std::is_convertible_v<cow::value<derived>, cow::value<derived>> == std::is_convertible_v<derived, derived>);
        CHECK(std::is_convertible_v<cow::value<derived>&, cow::value<derived>> == std::is_convertible_v<derived&, derived>);
        CHECK(cast<cow::value<derived>>(make<cow::value<derived>>())->gen == 0);
        CHECK(cast<cow::value<derived>>(lvalue(make<cow::value<derived>>()))->gen == 0);

        CHECK(std::is_convertible_v<cow::value<derived> const, cow::value<derived>> == std::is_convertible_v<derived const, derived>);
        CHECK(std::is_convertible_v<cow::value<derived> const&, cow::value<derived>> == std::is_convertible_v<derived const&, derived>);
        CHECK(cast<cow::value<derived>>(make<cow::value<derived> const>())->gen == 0);
        CHECK(cast<cow::value<derived>>(lvalue(make<cow::value<derived> const>()))->gen == 0);

        CHECK(std::is_convertible_v<cow::value<derived const>, cow::value<derived>> == std::is_convertible_v<derived const, derived>);
        CHECK(std::is_convertible_v<cow::value<derived const>&, cow::value<derived>> == std::is_convertible_v<derived const&, derived>);
        CHECK(cast<cow::value<derived>>(make<cow::value<derived const>>())->gen == 0);
        CHECK(cast<cow::value<derived>>(lvalue(make<cow::value<derived const>>()))->gen == 0);

        CHECK(std::is_convertible_v<cow::value<derived const> const, cow::value<derived>> == std::is_convertible_v<derived const, derived>);
        CHECK(std::is_convertible_v<cow::value<derived const> const&, cow::value<derived>> == std::is_convertible_v<derived const&, derived>);
        CHECK(cast<cow::value<derived>>(make<cow::value<derived const> const>())->gen == 0);
        CHECK(cast<cow::value<derived>>(lvalue(make<cow::value<derived const> const>()))->gen == 0);

        CHECK(std::is_convertible_v<cow::value<derived>, cow::value<derived const>> == std::is_convertible_v<derived, derived const>);
        CHECK(std::is_convertible_v<cow::value<derived>&, cow::value<derived const>> == std::is_convertible_v<derived&, derived const>);
        CHECK(cast<cow::value<derived const>>(make<cow::value<derived>>())->gen == 0);
        CHECK(cast<cow::value<derived const>>(lvalue(make<cow::value<derived>>()))->gen == 0);

        CHECK(std::is_convertible_v<cow::value<derived> const, cow::value<derived const>> == std::is_convertible_v<derived const, derived const>);
        CHECK(std::is_convertible_v<cow::value<derived> const&, cow::value<derived const>> == std::is_convertible_v<derived const&, derived const>);
        CHECK(cast<cow::value<derived const>>(make<cow::value<derived> const>())->gen == 0);
        CHECK(cast<cow::value<derived const>>(lvalue(make<cow::value<derived> const>()))->gen == 0);

        CHECK(std::is_convertible_v<cow::value<derived const>, cow::value<derived const>> == std::is_convertible_v<derived const, derived const>);
        CHECK(std::is_convertible_v<cow::value<derived const>&, cow::value<derived const>> == std::is_convertible_v<derived const&, derived const>);
        CHECK(cast<cow::value<derived const>>(make<cow::value<derived const>>())->gen == 0);
        CHECK(cast<cow::value<derived const>>(lvalue(make<cow::value<derived const>>()))->gen == 0);

        CHECK(std::is_convertible_v<cow::value<derived const> const, cow::value<derived const>> == std::is_convertible_v<derived const, derived const>);
        CHECK(std::is_convertible_v<cow::value<derived const> const&, cow::value<derived const>> == std::is_convertible_v<derived const&, derived const>);
        CHECK(cast<cow::value<derived const>>(make<cow::value<derived const> const>())->gen == 0);
        CHECK(cast<cow::value<derived const>>(lvalue(make<cow::value<derived const> const>()))->gen == 0);

        CHECK(std::is_convertible_v<cow::value<derived>, cow::value<base>> == std::is_convertible_v<derived, base>);
        CHECK(std::is_convertible_v<cow::value<derived>&, cow::value<base>> == std::is_convertible_v<derived&, base>);

        CHECK(std::is_convertible_v<cow::value<derived> const, cow::value<base>> == std::is_convertible_v<derived const, base>);
        CHECK(std::is_convertible_v<cow::value<derived> const&, cow::value<base>> == std::is_convertible_v<derived const&, base>);

        CHECK(std::is_convertible_v<cow::value<derived const>, cow::value<base>> == std::is_convertible_v<derived const, base>);
        CHECK(std::is_convertible_v<cow::value<derived const>&, cow::value<base>> == std::is_convertible_v<derived const&, base>);

        CHECK(std::is_convertible_v<cow::value<derived const> const, cow::value<base>> == std::is_convertible_v<derived const, base>);
        CHECK(std::is_convertible_v<cow::value<derived const> const&, cow::value<base>> == std::is_convertible_v<derived const&, base>);

        CHECK(std::is_convertible_v<cow::value<derived>, cow::value<base const>> == std::is_convertible_v<derived, base const>);
        CHECK(std::is_convertible_v<cow::value<derived>&, cow::value<base const>> == std::is_convertible_v<derived&, base const>);

        CHECK(std::is_convertible_v<cow::value<derived> const, cow::value<base const>> == std::is_convertible_v<derived const, base const>);
        CHECK(std::is_convertible_v<cow::value<derived> const&, cow::value<base const>> == std::is_convertible_v<derived const&, base const>);

        CHECK(std::is_convertible_v<cow::value<derived const>, cow::value<base const>> == std::is_convertible_v<derived const, base const>);
        CHECK(std::is_convertible_v<cow::value<derived const>&, cow::value<base const>> == std::is_convertible_v<derived const&, base const>);

        CHECK(std::is_convertible_v<cow::value<derived const> const, cow::value<base const>> == std::is_convertible_v<derived const, base const>);
        CHECK(std::is_convertible_v<cow::value<derived const> const&, cow::value<base const>> == std::is_convertible_v<derived const&, base const>);

        CHECK(std::is_convertible_v<cow::value<base>, cow::value<derived>> == std::is_convertible_v<base, derived>);
        CHECK(std::is_convertible_v<cow::value<base>&, cow::value<derived>> == std::is_convertible_v<base&, derived>);
        CHECK(cast<cow::value<derived>>(make<cow::value<base>>())->gen == 0);

        CHECK(std::is_convertible_v<cow::value<base> const, cow::value<derived>> == std::is_convertible_v<base const, derived>);
        CHECK(std::is_convertible_v<cow::value<base> const&, cow::value<derived>> == std::is_convertible_v<base const&, derived>);

        CHECK(std::is_convertible_v<cow::value<base const>, cow::value<derived>> == std::is_convertible_v<base const, derived>);
        CHECK(std::is_convertible_v<cow::value<base const>&, cow::value<derived>> == std::is_convertible_v<base const&, derived>);

        CHECK(std::is_convertible_v<cow::value<base const> const, cow::value<derived>> == std::is_convertible_v<base const, derived>);
        CHECK(std::is_convertible_v<cow::value<base const> const&, cow::value<derived>> == std::is_convertible_v<base const&, derived>);

        CHECK(std::is_convertible_v<cow::value<base>, cow::value<derived const>> == std::is_convertible_v<base, derived const>);
        CHECK(std::is_convertible_v<cow::value<base>&, cow::value<derived const>> == std::is_convertible_v<base&, derived const>);
        CHECK(cast<cow::value<derived const>>(make<cow::value<base>>())->gen == 0);

        CHECK(std::is_convertible_v<cow::value<base> const, cow::value<derived const>> == std::is_convertible_v<base const, derived const>);
        CHECK(std::is_convertible_v<cow::value<base> const&, cow::value<derived const>> == std::is_convertible_v<base const&, derived const>);

        CHECK(std::is_convertible_v<cow::value<base const>, cow::value<derived const>> == std::is_convertible_v<base const, derived const>);
        CHECK(std::is_convertible_v<cow::value<base const>&, cow::value<derived const>> == std::is_convertible_v<base const&, derived const>);

        CHECK(std::is_convertible_v<cow::value<base const> const, cow::value<derived const>> == std::is_convertible_v<base const, derived const>);
        CHECK(std::is_convertible_v<cow::value<base const> const&, cow::value<derived const>> == std::is_convertible_v<base const&, derived const>);

        CHECK(std::is_convertible_v<cow::value<base>, cow::value<qualifier>> == std::is_convertible_v<base, qualifier>);
        CHECK(std::is_convertible_v<cow::value<base>&, cow::value<qualifier>> == std::is_convertible_v<base&, qualifier>);

        CHECK(std::is_convertible_v<cow::value<base> const, cow::value<qualifier>> == std::is_convertible_v<base const, qualifier>);
        CHECK(std::is_convertible_v<cow::value<base> const&, cow::value<qualifier>> == std::is_convertible_v<base const&, qualifier>);

        CHECK(std::is_convertible_v<cow::value<base const>, cow::value<qualifier>> == std::is_convertible_v<base const, qualifier>);
        CHECK(std::is_convertible_v<cow::value<base const>&, cow::value<qualifier>> == std::is_convertible_v<base const&, qualifier>);

        CHECK(std::is_convertible_v<cow::value<base const> const, cow::value<qualifier>> == std::is_convertible_v<base const, qualifier>);
        CHECK(std::is_convertible_v<cow::value<base const> const&, cow::value<qualifier>> == std::is_convertible_v<base const&, qualifier>);

        CHECK(std::is_convertible_v<cow::value<base>, cow::value<qualifier const>> == std::is_convertible_v<base, qualifier const>);
        CHECK(std::is_convertible_v<cow::value<base>&, cow::value<qualifier const>> == std::is_convertible_v<base&, qualifier const>);

        CHECK(std::is_convertible_v<cow::value<base> const, cow::value<qualifier const>> == std::is_convertible_v<base const, qualifier const>);
        CHECK(std::is_convertible_v<cow::value<base> const&, cow::value<qualifier const>> == std::is_convertible_v<base const&, qualifier const>);

        CHECK(std::is_convertible_v<cow::value<base const>, cow::value<qualifier const>> == std::is_convertible_v<base const, qualifier const>);
        CHECK(std::is_convertible_v<cow::value<base const>&, cow::value<qualifier const>> == std::is_convertible_v<base const&, qualifier const>);

        CHECK(std::is_convertible_v<cow::value<base const> const, cow::value<qualifier const>> == std::is_convertible_v<base const, qualifier const>);
        CHECK(std::is_convertible_v<cow::value<base const> const&, cow::value<qualifier const>> == std::is_convertible_v<base const&, qualifier const>);

        CHECK(std::is_convertible_v<cow::value<derived>, cow::value<qualifier>> == std::is_convertible_v<derived, qualifier>);
        CHECK(std::is_convertible_v<cow::value<derived>&, cow::value<qualifier>> == std::is_convertible_v<derived&, qualifier>);
        CHECK(cast<cow::value<qualifier>>(make<cow::value<derived>>()) == qualifier::rref);
        CHECK(cast<cow::value<qualifier>>(lvalue(make<cow::value<derived>>())) == qualifier::lref);

        CHECK(std::is_convertible_v<cow::value<derived> const, cow::value<qualifier>> == std::is_convertible_v<derived const, qualifier>);
        CHECK(std::is_convertible_v<cow::value<derived> const&, cow::value<qualifier>> == std::is_convertible_v<derived const&, qualifier>);
        CHECK(cast<cow::value<qualifier>>(make<cow::value<derived> const>()) == qualifier::crref);
        CHECK(cast<cow::value<qualifier>>(lvalue(make<cow::value<derived> const>())) == qualifier::clref);

        CHECK(std::is_convertible_v<cow::value<derived const>, cow::value<qualifier>> == std::is_convertible_v<derived const, qualifier>);
        CHECK(std::is_convertible_v<cow::value<derived const>&, cow::value<qualifier>> == std::is_convertible_v<derived const&, qualifier>);
        CHECK(cast<cow::value<qualifier>>(make<cow::value<derived const>>()) == qualifier::crref);
        CHECK(cast<cow::value<qualifier>>(lvalue(make<cow::value<derived const>>())) == qualifier::clref);

        CHECK(std::is_convertible_v<cow::value<derived const> const, cow::value<qualifier>> == std::is_convertible_v<derived const, qualifier>);
        CHECK(std::is_convertible_v<cow::value<derived const> const&, cow::value<qualifier>> == std::is_convertible_v<derived const&, qualifier>);
        CHECK(cast<cow::value<qualifier>>(make<cow::value<derived const> const>()) == qualifier::crref);
        CHECK(cast<cow::value<qualifier>>(lvalue(make<cow::value<derived const> const>())) == qualifier::clref);

        CHECK(std::is_convertible_v<cow::value<derived>, cow::value<qualifier const>> == std::is_convertible_v<derived, qualifier const>);
        CHECK(std::is_convertible_v<cow::value<derived>&, cow::value<qualifier const>> == std::is_convertible_v<derived&, qualifier const>);
        CHECK(cast<cow::value<qualifier const>>(make<cow::value<derived>>()) == qualifier::rref);
        CHECK(cast<cow::value<qualifier const>>(lvalue(make<cow::value<derived>>())) == qualifier::lref);

        CHECK(std::is_convertible_v<cow::value<derived> const, cow::value<qualifier const>> == std::is_convertible_v<derived const, qualifier const>);
        CHECK(std::is_convertible_v<cow::value<derived> const&, cow::value<qualifier const>> == std::is_convertible_v<derived const&, qualifier const>);
        CHECK(cast<cow::value<qualifier const>>(make<cow::value<derived> const>()) == qualifier::crref);
        CHECK(cast<cow::value<qualifier const>>(lvalue(make<cow::value<derived> const>())) == qualifier::clref);

        CHECK(std::is_convertible_v<cow::value<derived const>, cow::value<qualifier const>> == std::is_convertible_v<derived const, qualifier const>);
        CHECK(std::is_convertible_v<cow::value<derived const>&, cow::value<qualifier const>> == std::is_convertible_v<derived const&, qualifier const>);
        CHECK(cast<cow::value<qualifier const>>(make<cow::value<derived const>>()) == qualifier::crref);
        CHECK(cast<cow::value<qualifier const>>(lvalue(make<cow::value<derived const>>())) == qualifier::clref);

        CHECK(std::is_convertible_v<cow::value<derived const> const, cow::value<qualifier const>> == std::is_convertible_v<derived const, qualifier const>);
        CHECK(std::is_convertible_v<cow::value<derived const> const&, cow::value<qualifier const>> == std::is_convertible_v<derived const&, qualifier const>);
        CHECK(cast<cow::value<qualifier const>>(make<cow::value<derived const> const>()) == qualifier::crref);
        CHECK(cast<cow::value<qualifier const>>(lvalue(make<cow::value<derived const> const>())) == qualifier::clref);
    }
}
