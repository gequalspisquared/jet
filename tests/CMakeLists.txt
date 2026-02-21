include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.13.0
)

FetchContent_MakeAvailable(Catch2)

#add_executable(jet_tests
#    EngineTests.cpp
#)

#target_link_libraries(jet_tests
#    PRIVATE
#        jet::jet_engine
#        Catch2::Catch2WithMain
#)

include(Catch)
catch_discover_tests(jet_tests)
