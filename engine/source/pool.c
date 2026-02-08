/**
 * \file            pool.c
 * \brief           Main source file for pool.h
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

#include "jet/pool.h"

#include "jet/assert.h"
#include "jet/memory.h"

void
_jetPoolInit(_JetPool* pool, isize size) {
    JET_ASSERT(pool != NULL);
    JET_ASSERT(size > 0);

    // Reserve 0 index for safety checks
    pool->size = size + 1;
    pool->generation_counter_list = _jetMallocZeroed(sizeof(_JetGeneration) * pool->size);
    pool->next_available_list = _jetMalloc(sizeof(_JetIndex) * pool->size);
    pool->top = 1;

    pool->next_available_list[0] = 0;
    for (isize i = 1; i < pool->size - 1; i++) {
        pool->next_available_list[i] = i + 1;
    }
    pool->next_available_list[pool->size - 1] = 0;
}

_JetHandle
_jetPoolAdd(_JetPool* pool) {
    JET_ASSERT(pool != NULL);
    JET_ASSERT(pool->top > 0);
    JET_ASSERT(pool->top < pool->size);
    JET_ASSERT(pool->next_available_list[pool->top] > 0);

    isize index = pool->top - 1;
    _JetHandle handle = (_JetHandle){
        .index = index,
        .generation = ++(pool->generation_counter_list[index]),
    };
    pool->top = pool->next_available_list[pool->top];

    return handle;
}

void
_jetPoolRemove(_JetPool* pool, _JetHandle handle) {
    JET_ASSERT(pool != NULL);
    JET_ASSERT(handle.index > 0);
    JET_ASSERT(handle.index < pool->size);
    JET_ASSERT(handle.generation
               == pool->generation_counter_list[handle.index]);

    pool->next_available_list[handle.index] = pool->top;
    pool->top = handle.index;
}

void
_jetPoolDeinit(_JetPool* pool) {
    JET_ASSERT(pool != NULL);
    JET_ASSERT(pool->generation_counter_list != NULL);
    JET_ASSERT(pool->next_available_list != NULL);

    _jetFree(pool->generation_counter_list);
    pool->generation_counter_list = NULL;
    _jetFree(pool->next_available_list);
    pool->next_available_list = NULL;
    pool->size = 0;
    pool->top = 0;
}

/*
JetPool jetCreatePool(u8* objects,
    u32 object_size,
    JetHandle* handles,
    u32* free_list,
    u32 free_count) {

    JetPool pool = (JetPool) {
        .objects = objects,
        .object_size = object_size,
        .handles = handles,
        .free_list = free_list,
        .free_count = free_count,
    };

    for (u32 i = 0; i < free_count; i++) {
        //storage.free_list[i] = MAX_WINDOWS - i - 1;
        pool.free_list[i] = free_count - i - 1;
        pool.handles[i].generation = 1;
    }

    return pool;
}
*/

/*
void _jetPoolInit(_JetPool* pool, usize size) {
    pool->size = size;

    for (u32 i = 0; i < pool->size; i++) {
        pool->free_list[pool->top++] = i;
    }
}

_JetHandle _jetPoolAdd(_JetPool* pool) {
    assert(pool->top > 0);
    assert(pool->top < pool->size); // Is this correct?
    u32 handle_index = pool->free_list[--pool->top];
    pool->handles[handle_index].index = handle_index;

    return pool->handles[handle_index];
}

void _jetPoolRemove(_JetPool* pool, _JetHandle handle)
{
    //assert(handle.index < MAX_WINDOWS);

    if (handle.generation
        != pool->handles[handle.index].generation) {
        printf("Stale handle!\n");
    }

    pool->handles[handle.index].generation++;
    pool->free_list[pool->top++] = handle.index;
}
*/

/*
void* _jetPoolGet(_JetPool* pool, _JetHandle handle) {
    // TODO: Assert?
    return pool->objects + handle.index * pool->object_size;
}
*/
