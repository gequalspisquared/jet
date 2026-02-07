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

#include "jet/memory.h"

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
#define MAX_WINDOWS 8

static JetWindow windows[MAX_WINDOWS];
static JetHandle window_handles[MAX_WINDOWS];
static u32 windows_free_list[MAX_WINDOWS];
//static u32 windows_free_count = 0;
//static JetStorage windows_storage {
//    .objects = windows;
//    .handles = window_handles;
//    .free_list = windows_free_list;
//    .free_count = 0;
//};
static JetStorage windows_storage;

static bool isInitialized = 0;

static void initializeWindows() {
    /*
    windows_free_count = MAX_WINDOWS;
    for (u32 i = 0; i < MAX_WINDOWS; i++) {
        windows_free_list[i] = MAX_WINDOWS - i - 1;
        window_handles[i].generation = 1;
    }
    */

    windows_storage = jetCreateStorage(
        windows, sizeof(JetWindow), window_handles, windows_free_list, MAX_WINDOWS);

    isInitialized = 1;
}

JetWindowHandle jetCreateWindow(i32 width, i32 height, string title) {
    assert(g_jetIsInitialized == 1);

    if (!isInitialized) {
        initializeWindows();
    }

    /*
    assert(windows_free_count > 0);
    u32 index = windows_free_list[--windows_free_count];
    windows_handles[index].index = index;
    */

    JetHandle jet_window_handle = jetStorageAdd(&windows_storage);
    JetWindow* jet_window = (JetWindow*)jetStorageGet(&windows_storage, jet_window_handle);

    SDL_WindowFlags window_flags = 0;
    SDL_Window* window = SDL_CreateWindow(title, width, height, window_flags);
    assert(window != NULL);

    // TODO: Hardcode bad
    //windows[index] = (JetWindow){
    //    .window = window,
	//	.title = title,
	//	.width = width,
	//	.height = height,
	//};

    jet_window->window = window;
    jet_window->title = title;
    jet_window->width = width;
    jet_window->height = height;

    printf("Created window with height: %d width: %d, title: %s\n",
           width,
           height,
           title);
    //return window_handles[index];
    return jet_window_handle;
}

// TODO: All of this handle stuff needs to be consolidated
void jetDestroyWindow(JetWindowHandle window_handle) {
    /*
    assert(window_handle.index < MAX_WINDOWS);

    if (window_handle.generation
        != window_handles[window_handle.index].generation) {
        printf("Stale window handle!\n");
    }

    window_handles[window_handle.index].generation++;
    window_free_list[window_free_count++] = window_handle.index;
    */

    jetStorageRemove(&windows_storage, window_handle);
}

void _jetCleanupWindows(void) {
    printf("Destroying window\n");

    //SDL_DestroyWindow(windows[1].window);
    // TODO: Find all actual windows and destroy them

}
