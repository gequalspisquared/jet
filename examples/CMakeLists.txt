# TODO:
#add_executable(MinimalExample
#    MinimalExample.cpp
#)

add_executable(build_test
    test/test.cpp
)

target_link_libraries(build_test
    PRIVATE
        jet::jet_engine
)
