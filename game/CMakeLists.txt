file(GLOB_RECURSE JET_GAME_SOURCES
    CONFIGURE_DEPENDS
    source/*.c
    source/*.h
)

add_executable(jet_game ${JET_GAME_SOURCES})

target_link_libraries(jet_game
    PRIVATE
        jet_engine
)

# Per-config output directories
set_target_properties(jet_game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
)

# Warnings
if (MSVC)
    target_compile_options(jet_game PRIVATE /W4)
else()
    target_compile_options(jet_game PRIVATE -Wall -Wextra -Wpedantic)
endif()
