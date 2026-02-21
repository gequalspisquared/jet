#include "jet.h"

#include <SDL3/SDL.h>

#include <iostream>

namespace jet {

Window* initWindow(const WindowDesc &desc) {
    const SDL_WindowFlags flags = 0;
    SDL_Window* window = SDL_CreateWindow(desc.title, desc.width, desc.height, flags);
    if (!window) {
        std::cout << "Failed to create a window!\n";
        return nullptr;
    }

    return new Window {
        .width = desc.width,
        .height = desc.height,
        .title = desc.title,
        .handle = window
    };
}

void deinitWindow(Window* window) {
    if (window->handle) {
        SDL_DestroyWindow((SDL_Window*)window->handle);
        window->handle = nullptr;
    }
}

}
