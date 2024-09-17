cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

add_library(refl INTERFACE refl/refl.hpp refl/registry.hpp)


target_include_directories(refl INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>   # Utilisé lors de la phase de build
    $<INSTALL_INTERFACE:include>  # Utilisé lors de l'installation
    )

install(DIRECTORY refl DESTINATION include)

install(TARGETS refl
        EXPORT reflTargets
        INCLUDES DESTINATION include/refl)

install(EXPORT reflTargets
        FILE reflConfig.cmake
        NAMESPACE refl::
        DESTINATION lib/cmake/refl)

