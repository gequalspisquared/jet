/**
 * \file            memory.h
 * \brief           Header for objects that manage memory
 */

/*
 * MIT License
 *
 * Copyright (c) 2026 Nicholas Crane
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

#ifndef JET_MEMORY_H
#define JET_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "consts.h"

typedef union {
    u32 handle;
    // TODO: Is this fine? Do we need to be concerned about endian-ness?
    struct {
        u16 index;
        u16 generation;
    };
} JetHandle;

typedef struct {
    u8* objects;
    u32 object_size;
    JetHandle* handles;
    u32* free_list;
    u32 free_count;
} JetStorage;

JetStorage jetCreateStorage(u8* objects,
                            u32 object_size,
                            JetHandle* handles,
                            u32* free_list,
                            u32 free_count);

JetHandle jetStorageAdd(JetStorage* storage);
void jetStorageRemove(JetStorage* storage, JetHandle handle);
void* jetStorageGet(JetStorage* storage, JetHandle handle);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* JET_MEMORY_H */
