cmake_minimum_required(VERSION 3.9)

include(cmake/Test.cmake)
include(cmake/Deploy.cmake)
include(cmake/Coverage.cmake)

project(Cow CXX)

set(COW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")

file(STRINGS "${COW_INCLUDE_DIR}/cow/version.hpp"
    COW_CONFIG_VERSION_HPP REGEX "COW_[A-Z]+ [0-9]+" LIMIT_COUNT 3
)

list(GET COW_CONFIG_VERSION_HPP 0 COW_MAJOR)
list(GET COW_CONFIG_VERSION_HPP 1 COW_MINOR)
list(GET COW_CONFIG_VERSION_HPP 2 COW_PATCH)

string(REGEX REPLACE ".*MAJOR ([0-9]+).*" "\\1" COW_MAJOR "${COW_MAJOR}")
string(REGEX REPLACE ".*MINOR ([0-9]+).*" "\\1" COW_MINOR "${COW_MINOR}")
string(REGEX REPLACE ".*PATCH ([0-9]+).*" "\\1" COW_PATCH "${COW_PATCH}")

set(COW_VERSION "${COW_MAJOR}.${COW_MINOR}.${COW_PATCH}")

message(STATUS "Configuring Cow ${COW_VERSION}")

add_header_library(Cow "${COW_INCLUDE_DIR}/cow.hpp" "LICENSE")
set_target_properties(Cow PROPERTIES
    INTERFACE_LIB_VERSION ${COW_VERSION}
    INTERFACE_COMPILE_FEATURES cxx_std_17
)

deploy_header_library(Cow)

add_subdirectory(test)
