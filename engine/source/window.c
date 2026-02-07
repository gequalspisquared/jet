/**
 * \file            window.c
 * \brief           Main source file for window.h
 */

/*
 * MIT License
 *
 * Copyright (c) 2025 Nicholas Crane
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "jet/window.h"

#include <SDL3/SDL.h>

#include <assert.h>
#include <stdio.h>

extern bool g_jetIsInitialized;

/*
typedef struct JetWindow {
    SDL_Window* window;
    string title;
    i32 width;
    i32 height;
} JetWindow;

JetWindow* jetInitWindow(i32 width, i32 height, string title) {
    assert(g_jetIsInitialized == 1);

    SDL_WindowFlags window_flags = NULL;
    SDL_Window* window = SDL_CreateWindow(title, width, height, window_flags);

    JetWindow* jet_window = malloc(sizeof(JetWindow));
    jet_window->window = window;
    jet_window->title = title;
    jet_window->width = width;
    jet_window->height = height;

    printf("Created window with height: %d width: %d, title: %s\n",
           width,
           height,
           title);
    return jet_window;
}

void jetDeinitWindow(JetWindow* window) {
    assert(window != NULL);

    printf("Destroying window\n");
    free(window);
}
*/

typedef struct JetWindow {
    SDL_Window* window;
    string title;
    i32 width;
    i32 height;
} JetWindow;

// This may need more thought...
static JetWindow windows[8];

JetWindowHandle jetCreateWindow(i32 width, i32 height, string title) {
    assert(g_jetIsInitialized == 1);

    SDL_WindowFlags window_flags = 0;
    SDL_Window* window = SDL_CreateWindow(title, width, height, window_flags);

    // TODO: Hardcode bad
    windows[1] = (JetWindow){
        .window = window,
		.title = title,
		.width = width,
		.height = height,
	};

    //windows[1] = jet_window;

    printf("Created window with height: %d width: %d, title: %s\n",
           width,
           height,
           title);
    return 1;
}

void _jetCleanupWindows(void) {
    printf("Destroying window\n");

    SDL_DestroyWindow(windows[1].window);
}
