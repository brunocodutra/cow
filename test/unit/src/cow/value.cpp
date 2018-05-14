#include <cow.hpp>
#include <test.hpp>

int main() {

    /* Value Semantics */ {

        cow::value a = 'a';
        cow::value b = a;
        cow::value c = a;

        assert(a == 'a');
        assert(b == 'a');
        assert(c == 'a');

        b = 'b';

        assert(a == 'a');
        assert(b == 'b');
        assert(c == 'a');

        c = 'c';

        assert(a == 'a');
        assert(b == 'b');
        assert(c == 'c');
    }

    /* Copy If Mutable */ {

        cow::value a = derived{};
        cow::value b = a;
        cow::value c = a;

        assert(a->gen == 0);
        assert(b->gen == 0);
        assert(c->gen == 0);

        assert(a.get().gen == 1);
        assert(b.get().gen == 1);
        assert(c.get().gen == 0);
    }

    /* Copy If Movable */ {

        cow::value a = derived{};
        cow::value b = a;
        cow::value c = a;

        assert(a->gen == 0);
        assert(b->gen == 0);
        assert(c->gen == 0);

        assert(std::move(a).get().gen == 1);
        assert(std::move(b).get().gen == 1);
        assert(std::move(c).get().gen == 0);
    }

    /* Don't Copy If Immutable */ {

        cow::value<derived> const a = derived{};
        cow::value<derived const> b = a;
        cow::value<derived const> const c = a;

        assert(a->gen == 0);
        assert(b->gen == 0);
        assert(c->gen == 0);

        assert(a.get().gen == 0);
        assert(b.get().gen == 0);
        assert(c.get().gen == 0);
    }

    /* Don't Copy If Immovable */ {

        cow::value<derived> const a = derived{};
        cow::value<derived const> b = a;
        cow::value<derived const> const c = a;

        assert(a->gen == 0);
        assert(b->gen == 0);
        assert(c->gen == 0);

        assert(std::move(a).get().gen == 0);
        assert(std::move(b).get().gen == 0);
        assert(std::move(c).get().gen == 0);
    }
}
