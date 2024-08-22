cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

add_executable(serialisation main.cpp)

target_link_libraries(serialisation refl)