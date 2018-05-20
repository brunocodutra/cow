# Cow [![version]][semver] [![travis.badge]][travis.cow] [![codecov.badge]][codecov.cow]
Good old copy on write

## Overview

**Cow** provides an easy way to seamlessly augment any copyable type with
lazy copy-on-write semantics.


```.cpp
#include "cow.hpp"

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

// consider a data type that is expensive to copy
struct expensive_to_copy {

    /* ... */

    expensive_to_copy() { /* ... */ };

    expensive_to_copy(expensive_to_copy const&) {

        /* ... */

        std::cout << "copied" << std::endl;

        /* ... */
    }

    void save_to_disk() const {

        /* ... */

        using namespace std::chrono_literals;

        std::cout << "saving..." << std::endl;
        std::this_thread::sleep_for(2s);
        std::cout << "saving complete" << std::endl;

        /* ... */
    }

    void mutate() {

        /* ... */

        std::cout << "mutated" << std::endl;

        /* ... */
    }

    /* ... */
};

// and a simple document type built around it
class document {

    cow::value<expensive_to_copy> data;

public:
    // save asynchronously
    std::future<void> save() const {

        // safely capture by value - no copy is performed
        return std::async([alias = data] {
            alias->save_to_disk();
        });
    }

    void update() {
        cow::unbox(data, [](expensive_to_copy& ref) {
            ref.mutate();
        });
    }
};

int main() {
    document doc;

    doc.update();           // no copy performed
    doc.save().get();       // no copy performed - blocks until finished
    doc.update();           // no copy performed
    auto fut = doc.save();  // no copy performed - runs asynchronously

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);

    doc.update(); // possible copy if the asynchronous operation hasn't completed yet
}
```

Probable output:

```
mutated
saving...
saving complete
mutated
saving...
copied
mutated
saving complete
```

## Quick Start

1. Download [cow.hpp][releases]
2. `# include </path/to/cow.hpp>`

## Portability

The following compilers are continuously tested on [Travis CI][travis.cow].

| Compiler          | Version   | Operating System |
|-------------------|-----------|------------------|
| GCC               | 7         | Ubuntu 14.04 LTS |
| GCC               | 8         | Ubuntu 14.04 LTS |
| Clang             | 5.0       | Ubuntu 14.04 LTS |
| Clang             | 6.0       | Ubuntu 14.04 LTS |

## License

This project is licensed under the [MIT][license].

[version]:          https://badge.fury.io/gh/brunocodutra%2Fcow.svg
[semver]:           https://semver.org

[travis.cow]:       https://travis-ci.org/brunocodutra/cow
[travis.badge]:     https://travis-ci.org/brunocodutra/cow.svg?branch=master

[codecov.cow]:      https://codecov.io/gh/brunocodutra/cow
[codecov.badge]:    https://codecov.io/gh/brunocodutra/cow/branch/master/graph/badge.svg

[license]:          https://github.com/brunocodutra/cow/blob/master/LICENSE
[releases]:         https://github.com/brunocodutra/cow/releases
