#include <cow.hpp>
#include <test.hpp>

int main() {

    /* Copy & Move */ {
        CHECK(std::is_assignable_v<cow::value<base>, base> == std::is_assignable_v<base, base>);
        CHECK(std::is_assignable_v<cow::value<base>, base&> == std::is_assignable_v<base, base&>);
        CHECK((make<cow::value<base>>() = make<base>())->gen == 0);
        CHECK((make<cow::value<base>>() = lvalue(make<base>()))->gen == 1);

        CHECK(std::is_assignable_v<cow::value<base>, base const> == std::is_assignable_v<base, base const>);
        CHECK(std::is_assignable_v<cow::value<base>, base const&> == std::is_assignable_v<base, base const&>);
        CHECK((make<cow::value<base>>() = make<base const>())->gen == 1);
        CHECK((make<cow::value<base>>() = lvalue(make<base const>()))->gen == 1);

        CHECK(std::is_assignable_v<cow::value<base const>, base> == std::is_assignable_v<base const, base>);
        CHECK(std::is_assignable_v<cow::value<base const>, base&> == std::is_assignable_v<base const, base&>);

        CHECK(std::is_assignable_v<cow::value<base const>, base const> == std::is_assignable_v<base const, base const>);
        CHECK(std::is_assignable_v<cow::value<base const>, base const&> == std::is_assignable_v<base const, base const&>);

        CHECK(std::is_assignable_v<cow::value<derived>, derived> == std::is_assignable_v<derived, derived>);
        CHECK(std::is_assignable_v<cow::value<derived>, derived&> == std::is_assignable_v<derived, derived&>);
        CHECK((make<cow::value<derived>>() = make<derived>())->gen == 0);
        CHECK((make<cow::value<derived>>() = lvalue(make<derived>()))->gen == 1);

        CHECK(std::is_assignable_v<cow::value<derived>, derived const> == std::is_assignable_v<derived, derived const>);
        CHECK(std::is_assignable_v<cow::value<derived>, derived const&> == std::is_assignable_v<derived, derived const&>);
        CHECK((make<cow::value<derived>>() = make<derived const>())->gen == 1);
        CHECK((make<cow::value<derived>>() = lvalue(make<derived const>()))->gen == 1);

        CHECK(std::is_assignable_v<cow::value<derived const>, derived> == std::is_assignable_v<derived const, derived>);
        CHECK(std::is_assignable_v<cow::value<derived const>, derived&> == std::is_assignable_v<derived const, derived&>);

        CHECK(std::is_assignable_v<cow::value<derived const>, derived const> == std::is_assignable_v<derived const, derived const>);
        CHECK(std::is_assignable_v<cow::value<derived const>, derived const&> == std::is_assignable_v<derived const, derived const&>);

        CHECK(std::is_assignable_v<cow::value<base>, derived> == std::is_assignable_v<base, derived>);
        CHECK(std::is_assignable_v<cow::value<base>, derived&> == std::is_assignable_v<base, derived&>);
        CHECK((make<cow::value<base>>() = make<derived>())->gen == 0);
        CHECK((make<cow::value<base>>() = lvalue(make<derived>()))->gen == 1);

        CHECK(std::is_assignable_v<cow::value<base>, derived const> == std::is_assignable_v<base, derived const>);
        CHECK(std::is_assignable_v<cow::value<base>, derived const&> == std::is_assignable_v<base, derived const&>);
        CHECK((make<cow::value<base>>() = make<derived const>())->gen == 1);
        CHECK((make<cow::value<base>>() = lvalue(make<derived const>()))->gen == 1);

        CHECK(std::is_assignable_v<cow::value<base const>, derived> == std::is_assignable_v<base const, derived>);
        CHECK(std::is_assignable_v<cow::value<base const>, derived&> == std::is_assignable_v<base const, derived&>);

        CHECK(std::is_assignable_v<cow::value<base const>, derived const> == std::is_assignable_v<base const, derived const>);
        CHECK(std::is_assignable_v<cow::value<base const>, derived const&> == std::is_assignable_v<base const, derived const&>);
    }

    /* Forwarding */ {
        CHECK(std::is_assignable_v<cow::value<derived>, base> == std::is_assignable_v<derived, base>);
        CHECK(std::is_assignable_v<cow::value<derived>, base&> == std::is_assignable_v<derived, base&>);
        CHECK((make<cow::value<derived>>() = make<base>())->gen == 0);

        CHECK(std::is_assignable_v<cow::value<derived>, base const> == std::is_assignable_v<derived, base const>);
        CHECK(std::is_assignable_v<cow::value<derived>, base const&> == std::is_assignable_v<derived, base const&>);

        CHECK(std::is_assignable_v<cow::value<derived const>, base> == std::is_assignable_v<derived const, base>);
        CHECK(std::is_assignable_v<cow::value<derived const>, base&> == std::is_assignable_v<derived const, base&>);

        CHECK(std::is_assignable_v<cow::value<derived const>, base const> == std::is_assignable_v<derived const, base const>);
        CHECK(std::is_assignable_v<cow::value<derived const>, base const&> == std::is_assignable_v<derived const, base const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier>, base> == std::is_assignable_v<qualifier&, base>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, base&> == std::is_assignable_v<qualifier&, base&>);

        CHECK(std::is_assignable_v<cow::value<qualifier>, base const> == std::is_assignable_v<qualifier&, base const>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, base const&> == std::is_assignable_v<qualifier&, base const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, base> == std::is_assignable_v<qualifier const&, base>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, base&> == std::is_assignable_v<qualifier const&, base&>);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, base const> == std::is_assignable_v<qualifier const&, base const>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, base const&> == std::is_assignable_v<qualifier const&, base const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier>, derived> == std::is_assignable_v<qualifier&, derived>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, derived&> == std::is_assignable_v<qualifier&, derived&>);
        CHECK((make<cow::value<qualifier>>() = make<cow::value<derived>>()) == qualifier::rref);
        CHECK((make<cow::value<qualifier>>() = lvalue(make<cow::value<derived>>())) == qualifier::lref);

        CHECK(std::is_assignable_v<cow::value<qualifier>, derived const> == std::is_assignable_v<qualifier&, derived const>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, derived const&> == std::is_assignable_v<qualifier&, derived const&>);
        CHECK((make<cow::value<qualifier>>() = make<cow::value<derived> const>()) == qualifier::crref);
        CHECK((make<cow::value<qualifier>>() = lvalue(make<cow::value<derived> const>())) == qualifier::clref);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, derived> == std::is_assignable_v<qualifier const&, derived>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, derived&> == std::is_assignable_v<qualifier const&, derived&>);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, derived const> == std::is_assignable_v<qualifier const&, derived const>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, derived const&> == std::is_assignable_v<qualifier const&, derived const&>);
    }

    /* Aliasing */ {
        CHECK(std::is_assignable_v<cow::value<base>, cow::value<base>> == std::is_assignable_v<base, base>);
        CHECK(std::is_assignable_v<cow::value<base>, cow::value<base>&> == std::is_assignable_v<base, base&>);
        CHECK((make<cow::value<base>>() = make<cow::value<base>>())->gen == 0);
        CHECK((make<cow::value<base>>() = lvalue(make<cow::value<base>>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<base>, cow::value<base> const> == std::is_assignable_v<base, base const>);
        CHECK(std::is_assignable_v<cow::value<base>, cow::value<base> const&> == std::is_assignable_v<base, base const&>);
        CHECK((make<cow::value<base>>() = make<cow::value<base> const>())->gen == 0);
        CHECK((make<cow::value<base>>() = lvalue(make<cow::value<base> const>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<base>, cow::value<base const>> == std::is_assignable_v<base, base const>);
        CHECK(std::is_assignable_v<cow::value<base>, cow::value<base const>&> == std::is_assignable_v<base, base const&>);
        CHECK((make<cow::value<base>>() = make<cow::value<base const>>())->gen == 0);
        CHECK((make<cow::value<base>>() = lvalue(make<cow::value<base const>>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<base>, cow::value<base const> const> == std::is_assignable_v<base, base const>);
        CHECK(std::is_assignable_v<cow::value<base>, cow::value<base const> const&> == std::is_assignable_v<base, base const&>);
        CHECK((make<cow::value<base>>() = make<cow::value<base const> const>())->gen == 0);
        CHECK((make<cow::value<base>>() = lvalue(make<cow::value<base const> const>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<base>> == std::is_assignable_v<base const, base>);
        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<base>&> == std::is_assignable_v<base const, base&>);

        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<base> const> == std::is_assignable_v<base const, base const>);
        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<base> const&> == std::is_assignable_v<base const, base const&>);

        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<base const>> == std::is_assignable_v<base const, base const>);
        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<base const>&> == std::is_assignable_v<base const, base const&>);

        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<base const> const> == std::is_assignable_v<base const, base const>);
        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<base const> const&> == std::is_assignable_v<base const, base const&>);

        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<derived>> == std::is_assignable_v<derived, derived>);
        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<derived>&> == std::is_assignable_v<derived, derived&>);
        CHECK((make<cow::value<derived>>() = make<cow::value<derived>>())->gen == 0);
        CHECK((make<cow::value<derived>>() = lvalue(make<cow::value<derived>>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<derived> const> == std::is_assignable_v<derived, derived const>);
        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<derived> const&> == std::is_assignable_v<derived, derived const&>);
        CHECK((make<cow::value<derived>>() = make<cow::value<derived> const>())->gen == 0);
        CHECK((make<cow::value<derived>>() = lvalue(make<cow::value<derived> const>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<derived const>> == std::is_assignable_v<derived, derived const>);
        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<derived const>&> == std::is_assignable_v<derived, derived const&>);
        CHECK((make<cow::value<derived>>() = make<cow::value<derived const>>())->gen == 0);
        CHECK((make<cow::value<derived>>() = lvalue(make<cow::value<derived const>>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<derived const> const> == std::is_assignable_v<derived, derived const>);
        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<derived const> const&> == std::is_assignable_v<derived, derived const&>);
        CHECK((make<cow::value<derived>>() = make<cow::value<derived const> const>())->gen == 0);
        CHECK((make<cow::value<derived>>() = lvalue(make<cow::value<derived const> const>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<derived>> == std::is_assignable_v<derived const, derived>);
        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<derived>&> == std::is_assignable_v<derived const, derived&>);

        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<derived> const> == std::is_assignable_v<derived const, derived const>);
        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<derived> const&> == std::is_assignable_v<derived const, derived const&>);

        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<derived const>> == std::is_assignable_v<derived const, derived const>);
        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<derived const>&> == std::is_assignable_v<derived const, derived const&>);

        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<derived const> const> == std::is_assignable_v<derived const, derived const>);
        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<derived const> const&> == std::is_assignable_v<derived const, derived const&>);

        CHECK(std::is_assignable_v<cow::value<base>, cow::value<derived>> == std::is_assignable_v<base, derived>);
        CHECK(std::is_assignable_v<cow::value<base>, cow::value<derived>&> == std::is_assignable_v<base, derived&>);
        CHECK((make<cow::value<base>>() = make<cow::value<derived>>())->gen == 0);
        CHECK((make<cow::value<base>>() = lvalue(make<cow::value<derived>>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<base>, cow::value<derived> const> == std::is_assignable_v<base, derived const>);
        CHECK(std::is_assignable_v<cow::value<base>, cow::value<derived> const&> == std::is_assignable_v<base, derived const&>);
        CHECK((make<cow::value<base>>() = make<cow::value<derived> const>())->gen == 0);
        CHECK((make<cow::value<base>>() = lvalue(make<cow::value<derived> const>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<base>, cow::value<derived const>> == std::is_assignable_v<base, derived const>);
        CHECK(std::is_assignable_v<cow::value<base>, cow::value<derived const>&> == std::is_assignable_v<base, derived const&>);
        CHECK((make<cow::value<base>>() = make<cow::value<derived const>>())->gen == 0);
        CHECK((make<cow::value<base>>() = lvalue(make<cow::value<derived const>>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<base>, cow::value<derived const> const> == std::is_assignable_v<base, derived const>);
        CHECK(std::is_assignable_v<cow::value<base>, cow::value<derived const> const&> == std::is_assignable_v<base, derived const&>);
        CHECK((make<cow::value<base>>() = make<cow::value<derived const> const>())->gen == 0);
        CHECK((make<cow::value<base>>() = lvalue(make<cow::value<derived const> const>()))->gen == 0);

        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<derived>> == std::is_assignable_v<base const, derived>);
        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<derived>&> == std::is_assignable_v<base const, derived&>);

        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<derived> const> == std::is_assignable_v<base const, derived const>);
        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<derived> const&> == std::is_assignable_v<base const, derived const&>);

        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<derived const>> == std::is_assignable_v<base const, derived const>);
        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<derived const>&> == std::is_assignable_v<base const, derived const&>);

        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<derived const> const> == std::is_assignable_v<base const, derived const>);
        CHECK(std::is_assignable_v<cow::value<base const>, cow::value<derived const> const&> == std::is_assignable_v<base const, derived const&>);

        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<base>> == std::is_assignable_v<derived, base>);
        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<base>&> == std::is_assignable_v<derived, base&>);
        CHECK((make<cow::value<derived>>() = make<cow::value<base>>())->gen == 0);

        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<base> const> == std::is_assignable_v<derived, base const>);
        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<base> const&> == std::is_assignable_v<derived, base const&>);

        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<base const>> == std::is_assignable_v<derived, base const>);
        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<base const>&> == std::is_assignable_v<derived, base const&>);

        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<base const> const> == std::is_assignable_v<derived, base const>);
        CHECK(std::is_assignable_v<cow::value<derived>, cow::value<base const> const&> == std::is_assignable_v<derived, base const&>);

        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<base>> == std::is_assignable_v<derived const, base>);
        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<base>&> == std::is_assignable_v<derived const, base&>);

        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<base> const> == std::is_assignable_v<derived const, base const>);
        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<base> const&> == std::is_assignable_v<derived const, base const&>);

        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<base const>> == std::is_assignable_v<derived const, base const>);
        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<base const>&> == std::is_assignable_v<derived const, base const&>);

        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<base const> const> == std::is_assignable_v<derived const, base const>);
        CHECK(std::is_assignable_v<cow::value<derived const>, cow::value<base const> const&> == std::is_assignable_v<derived const, base const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<base>> == std::is_assignable_v<qualifier&, base>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<base>&> == std::is_assignable_v<qualifier&, base&>);

        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<base> const> == std::is_assignable_v<qualifier&, base const>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<base> const&> == std::is_assignable_v<qualifier&, base const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<base const>> == std::is_assignable_v<qualifier&, base const>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<base const>&> == std::is_assignable_v<qualifier&, base const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<base const> const> == std::is_assignable_v<qualifier&, base const>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<base const> const&> == std::is_assignable_v<qualifier&, base const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<base>> == std::is_assignable_v<qualifier const&, base>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<base>&> == std::is_assignable_v<qualifier const&, base&>);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<base> const> == std::is_assignable_v<qualifier const&, base const>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<base> const&> == std::is_assignable_v<qualifier const&, base const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<base const>> == std::is_assignable_v<qualifier const&, base const>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<base const>&> == std::is_assignable_v<qualifier const&, base const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<base const> const> == std::is_assignable_v<qualifier const&, base const>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<base const> const&> == std::is_assignable_v<qualifier const&, base const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<derived>> == std::is_assignable_v<qualifier&, derived>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<derived>&> == std::is_assignable_v<qualifier&, derived&>);
        CHECK((make<cow::value<qualifier>>() = make<cow::value<derived>>()) == qualifier::rref);
        CHECK((make<cow::value<qualifier>>() = lvalue(make<cow::value<derived>>())) == qualifier::lref);

        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<derived> const> == std::is_assignable_v<qualifier&, derived const>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<derived> const&> == std::is_assignable_v<qualifier&, derived const&>);
        CHECK((make<cow::value<qualifier>>() = make<cow::value<derived> const>()) == qualifier::crref);
        CHECK((make<cow::value<qualifier>>() = lvalue(make<cow::value<derived> const>())) == qualifier::clref);

        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<derived const>> == std::is_assignable_v<qualifier&, derived const>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<derived const>&> == std::is_assignable_v<qualifier&, derived const&>);
        CHECK((make<cow::value<qualifier>>() = make<cow::value<derived const>>()) == qualifier::crref);
        CHECK((make<cow::value<qualifier>>() = lvalue(make<cow::value<derived const>>())) == qualifier::clref);

        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<derived const> const> == std::is_assignable_v<qualifier&, derived const>);
        CHECK(std::is_assignable_v<cow::value<qualifier>, cow::value<derived const> const&> == std::is_assignable_v<qualifier&, derived const&>);
        CHECK((make<cow::value<qualifier>>() = make<cow::value<derived const> const>()) == qualifier::crref);
        CHECK((make<cow::value<qualifier>>() = lvalue(make<cow::value<derived const> const>())) == qualifier::clref);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<derived>> == std::is_assignable_v<qualifier const&, derived>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<derived>&> == std::is_assignable_v<qualifier const&, derived&>);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<derived> const> == std::is_assignable_v<qualifier const&, derived const>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<derived> const&> == std::is_assignable_v<qualifier const&, derived const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<derived const>> == std::is_assignable_v<qualifier const&, derived const>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<derived const>&> == std::is_assignable_v<qualifier const&, derived const&>);

        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<derived const> const> == std::is_assignable_v<qualifier const&, derived const>);
        CHECK(std::is_assignable_v<cow::value<qualifier const>, cow::value<derived const> const&> == std::is_assignable_v<qualifier const&, derived const&>);
    }
}
