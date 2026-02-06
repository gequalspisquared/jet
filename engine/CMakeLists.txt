# Collect engine sources
file(GLOB_RECURSE JET_ENGINE_SOURCES
    CONFIGURE_DEPENDS
    source/*.c
    source/*.h
)

add_library(jet_engine STATIC ${JET_ENGINE_SOURCES})

# Public headers (exported to users of the engine)
target_include_directories(jet_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Warnings
if (MSVC)
    target_compile_options(jet_engine PRIVATE /W4)
else()
    target_compile_options(jet_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()
