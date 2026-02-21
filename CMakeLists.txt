cmake_minimum_required(VERSION 3.20)
project(
    jet
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(JET_ENGINE_BUILD_TESTS "Build tests" OFF)
option(JET_ENGINE_BUILD_EXAMPLES "Build examples" ON)

include(vendor.cmake)

add_subdirectory(core)

if(JET_ENGINE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(JET_ENGINE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
