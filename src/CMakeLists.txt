cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

add_library(refl INTERFACE refl/refl.hpp refl/registry.hpp)

target_include_directories(refl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(refl::refl ALIAS refl)

