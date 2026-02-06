include(FetchContent)

# -----------------------------
# SDL3
# -----------------------------
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.2.0 # or main if you want bleeding-edge
)

FetchContent_MakeAvailable(SDL3)

# -----------------------------
# sokol
# -----------------------------
FetchContent_Declare(
    sokol
    GIT_REPOSITORY https://github.com/floooh/sokol.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(sokol)

# -----------------------------
# cglm
# -----------------------------
FetchContent_Declare(
    cglm
    GIT_REPOSITORY https://github.com/recp/cglm.git
    GIT_TAG        master
)

# cglm is pure C, no need to build tests
set(CGLM_SHARED OFF CACHE BOOL "" FORCE)
set(CGLM_STATIC ON  CACHE BOOL "" FORCE)
set(CGLM_TESTS  OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(cglm)
