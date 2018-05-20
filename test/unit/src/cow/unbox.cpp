#include <cow.hpp>
#include <test.hpp>

int main() {

    /* Implicitly Immutable */ {

        cow::value a = derived{};
        cow::value const b = a; // alias

        cow::unbox(a, [](auto& val) {
            CHECK(std::is_same_v<decltype(val), derived const&>);
            CHECK(val.gen == 0);
        });

        cow::unbox(std::move(a), [](auto&& val) {
            CHECK(std::is_same_v<decltype(val), derived const&&>);
            CHECK(val.gen == 0);
        });
    }

    /* Explicitly Mutable */ {

        cow::value a = derived{};
        cow::value const b = a; // alias

        cow::unbox(a, [](derived& val) {
            CHECK(val.gen == 1);
        });

        cow::unbox(std::move(a), [](derived&& val) {
            CHECK(val.gen == 1);
        });
    }
}
