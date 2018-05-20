#include <cow.hpp>
#include <test.hpp>

int main() {

    /* Value Semantics */ {

        cow::value a = 'a';
        cow::value b = a;
        cow::value c = a;

        CHECK(a == 'a');
        CHECK(b == 'a');
        CHECK(c == 'a');

        b = 'b';

        CHECK(a == 'a');
        CHECK(b == 'b');
        CHECK(c == 'a');

        c = 'c';

        CHECK(a == 'a');
        CHECK(b == 'b');
        CHECK(c == 'c');
    }

    /* Copy If Mutable */ {

        cow::value a = derived{};
        cow::value b = a;
        cow::value c = a;

        CHECK(a->gen == 0);
        CHECK(b->gen == 0);
        CHECK(c->gen == 0);

        CHECK(a.get().gen == 1);
        CHECK(b.get().gen == 1);
        CHECK(c.get().gen == 0);
    }

    /* Copy If Movable */ {

        cow::value a = derived{};
        cow::value b = a;
        cow::value c = a;

        CHECK(a->gen == 0);
        CHECK(b->gen == 0);
        CHECK(c->gen == 0);

        CHECK(std::move(a).get().gen == 1);
        CHECK(std::move(b).get().gen == 1);
        CHECK(std::move(c).get().gen == 0);
    }

    /* Don't Copy If Immutable */ {

        cow::value<derived> const a = derived{};
        cow::value<derived const> b = a;
        cow::value<derived const> const c = a;

        CHECK(a->gen == 0);
        CHECK(b->gen == 0);
        CHECK(c->gen == 0);

        CHECK(a.get().gen == 0);
        CHECK(b.get().gen == 0);
        CHECK(c.get().gen == 0);
    }

    /* Don't Copy If Immovable */ {

        cow::value<derived> const a = derived{};
        cow::value<derived const> b = a;
        cow::value<derived const> const c = a;

        CHECK(a->gen == 0);
        CHECK(b->gen == 0);
        CHECK(c->gen == 0);

        CHECK(std::move(a).get().gen == 0);
        CHECK(std::move(b).get().gen == 0);
        CHECK(std::move(c).get().gen == 0);
    }
}
