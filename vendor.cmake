include(FetchContent)

# -----------------------------
# SDL3
# -----------------------------
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.2
)

FetchContent_MakeAvailable(SDL3)

# -----------------------------
# glm
# -----------------------------
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG        1.0.3
)

FetchContent_MakeAvailable(glm)
