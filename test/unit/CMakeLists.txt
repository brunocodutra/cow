add_definitions(-DEXPECTED_COW_MAJOR=${COW_MAJOR})
add_definitions(-DEXPECTED_COW_MINOR=${COW_MINOR})
add_definitions(-DEXPECTED_COW_PATCH=${COW_PATCH})

test_units(test.unit Cow "${CMAKE_CURRENT_SOURCE_DIR}/src")
