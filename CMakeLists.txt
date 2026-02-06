cmake_minimum_required(VERSION 3.16)

project(jet
    VERSION 0.1.0
    LANGUAGES C
)

# ---- C standard ----
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Default build type (single-config generators)
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING
        "Choose the type of build (Debug or Release)" FORCE)
endif()

# Output binaries to bin/<config>
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Subprojects
add_subdirectory(engine)
add_subdirectory(game)
