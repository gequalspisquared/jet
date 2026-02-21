add_library(jet_engine STATIC)

target_sources(jet_engine
    PRIVATE
        include/jet.h
        source/jet.cpp
)

target_include_directories(jet_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(jet_engine PRIVATE /W4)
else()
    target_compile_options(jet_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_library(jet::jet_engine ALIAS jet_engine)

target_link_libraries(jet_engine
    PRIVATE
        SDL3::SDL3
        glm::glm
)
