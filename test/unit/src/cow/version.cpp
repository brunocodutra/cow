#include <cow.hpp>

#if EXPECTED_COW_MAJOR != COW_MAJOR
#error major version mismatch!
#endif

#if EXPECTED_COW_MINOR != COW_MINOR
#error minor version mismatch!
#endif

#if EXPECTED_COW_PATCH != COW_PATCH
#error patch version mismatch!
#endif

#define EXPECTED_COW_VERSION COW_SEMVER( \
    EXPECTED_COW_MAJOR, \
    EXPECTED_COW_MINOR, \
    EXPECTED_COW_PATCH \
)

#if EXPECTED_COW_VERSION != COW_VERSION
#error semantic version mismatch!
#endif

int main() {}
