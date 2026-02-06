# Collect engine sources
file(GLOB_RECURSE JET_ENGINE_SOURCES
    CONFIGURE_DEPENDS
    source/*.c
    source/*.h
    include/*.h
)

add_library(jet_engine STATIC ${JET_ENGINE_SOURCES})

target_link_libraries(jet_engine
    PRIVATE
		SDL3::SDL3
		cglm
)

target_include_directories(jet_engine
    PRIVATE
        ${sokol_SOURCE_DIR}
)

set_target_properties(jet_engine PROPERTIES LINKER_LANGUAGE C)

# Public headers (exported to users of the engine)
target_include_directories(jet_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(jet_engine PUBLIC c_std_99)

# Warnings
if (MSVC)
    target_compile_options(jet_engine PRIVATE /W4)
else()
    target_compile_options(jet_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()
