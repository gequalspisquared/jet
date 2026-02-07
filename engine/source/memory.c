/**
 * \file            memory.c
 * \brief           Main source file for memory.h
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

#include "jet/memory.h"

#include <assert.h>

JetStorage jetCreateStorage(u8* objects,
    u32 object_size,
    JetHandle* handles,
    u32* free_list,
    u32 free_count) {

    JetStorage storage = (JetStorage) {
        .objects = objects,
        .object_size = object_size,
        .handles = handles,
        .free_list = free_list,
        .free_count = free_count,
    };

    for (u32 i = 0; i < free_count; i++) {
        //storage.free_list[i] = MAX_WINDOWS - i - 1;
        storage.free_list[i] = free_count - i - 1;
        storage.handles[i].generation = 1;
    }

    return storage;
}

JetHandle
jetStorageAdd(JetStorage* storage) {
    assert(storage->free_count > 0);
    u32 handle_index = storage->free_list[--storage->free_count];
    storage->handles[handle_index].index = handle_index;

    return storage->handles[handle_index];
}

void jetStorageRemove(JetStorage* storage, JetHandle handle)
{
    //assert(handle.index < MAX_WINDOWS);

    if (handle.generation
        != storage->handles[handle.index].generation) {
        printf("Stale handle!\n");
    }

    storage->handles[handle.index].generation++;
    storage->free_list[storage->free_count++] = handle.index;
}

void* jetStorageGet(JetStorage* storage, JetHandle handle) {
    // TODO: Assert?
    return storage->objects + handle.index * storage->object_size;
}
