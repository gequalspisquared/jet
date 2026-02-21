#include "jet.h"

#include <SDL3/SDL.h>

namespace jet
{

bool initialize() {
    const SDL_InitFlags init_flags = 0;
    SDL_Init(init_flags);

    return true;
}

void shutdown() {
    SDL_Quit();
}

};
