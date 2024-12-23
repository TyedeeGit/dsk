/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file dsrt_memory.h
 * @author Gianmarco Lenzi
 * @brief Memory management header for the DSRT library.
 */

#pragma once
#include "common.h"

#ifdef __cplusplus
#include <cstdbool>
#include <cstdlib>
#include <cstdio>
#else
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <mem.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Term allocator arguments type.
 */
typedef union {
    /**
     * @brief Size arguments.
     */
    DSRTSizeArgs      args;

    /**
     * @brief Size arguments array.
     */
    DSRTSizeArgsArray args_array;
} DSRTAllocatorArgs;

/**
* @brief Term allocator type.
*/
typedef struct {
    /**
     * @brief Get the actual size from size arguments.
     * @param args Size arguments.
     * @return Actual size.
     */
    DSRTSize (*_get_arg_size)(DSRTSizeArgs args);

    /**
     * @brief Allocate contiguous memory.
     * @param args_array Size arguments array.
     * @return Allocated term.
     */
    DSRTTerm (*_calloc)(DSRTSizeArgsArray args_array);

    /**
     * @brief Resize contiguous memory.
     * @param term Term to reallocate.
     * @param old_args_array Old size arguments array.
     * @param new_args_array New size arguments array.
     * @return Resized term.
     */
    DSRTTerm (*_cesize)(DSRTTerm term, DSRTSizeArgsArray old_args_array, DSRTSizeArgsArray new_args_array);

    /**
     * @brief Free contiguous memory.
     * @param term Term to free.
     */
    void     (*_free)(DSRTTerm term);
} DSRTTermAllocator;

/**
 * @brief Term object type.
 */
typedef struct {
    /**
     * @brief True when the object is freed.
     */
    bool freed;

    /**
     * @brief True if the object is an array.
     */
    bool              is_array;

    /**
     * @brief Object index.
     */
    DSRTIndex         ind;

    /**
     * @brief Term.
     */
    DSRTTerm          obj;

    /**
     * @brief Allocator to use.
     */
    DSRTTermAllocator allocator;

    /**
     * @brief Allocator arguments.
     */
    DSRTAllocatorArgs allocator_args;
} DSRTTermObject;

/**
 * @brief Array type of `num` elements of size `size`.
 */
typedef struct {
    /**
     * @brief Number of elements.
     */
    DSRTSize num;

    /**
     * @brief Element size.
     */
    DSRTSize size;
} DSRTArrayDescriptor;

/**
 * @brief Simple allocator type.
 */
typedef struct {
    /**
     * @brief True if the allocator is an array.
     */
    bool is_array;

    /**
     * @brief Allocator descriptor.
     */
    union {
        /**
         * @brief Size of the object if single.
         */
        DSRTSize            size_of;

        /**
         * @brief Array descriptor if array.
         */
        DSRTArrayDescriptor array_of;
    } descriptor;
} DSRTSimpleAllocator;

/**
 * @brief Simple object type.
 */
typedef struct {
    /**
     * @brief Object index.
     */
    DSRTIndex ind;

    /**
     * @brief Object.
     */
    DSRTAny obj;

    /**
     * @brief Allocator to use.
     */
    DSRTSimpleAllocator allocator;
} DSRTSimpleObject;

/**
 * @brief Get the size from a simple allocator.
 * @param allocator Simple allocator.
 * @return Size.
 */
DSRTSize dsrt_simple_get_alloc_size(DSRTSimpleAllocator allocator);

/**
 * @brief Get the size of a simple object.
 * @param obj Simple object.
 * @return Size.
 */
DSRTSize dsrt_simple_get_obj_size(DSRTSimpleObject obj);

/**
 * @brief The global simple object heap size.
 */
static DSRTSize dsrt_simple_heap_size;

/**
 * @brief The global simple object heap capacity.
 */
static DSRTSize dsrt_simple_heap_capacity;

/**
 * @brief The global simple object heap.
 */
static DSRTSimpleObject **dsrt_simple_heap;

/**
 * @brief Initialize the global simple object heap.
 */
void dsrt_simple_heap_init(void);

/**
 * @brief Allocate a simple object.
 * @param allocator Simple allocator to use.
 * @return Simple object.
 */
DSRTSimpleObject dsrt_simple_new(DSRTSimpleAllocator allocator);

/**
 * @brief Delete a simple object.
 * @param obj Simple object to delete.
 */
void dsrt_simple_del(DSRTSimpleObject obj);

/**
 * @brief Uninitialize the global simple object heap.
 */
void dsrt_simple_heap_exit(void);

/**
 * @brief The global term object heap size.
 */
static DSRTSize dsrt_term_heap_size;

/**
 * @brief The global term object heap capacity.
 */
static DSRTSize dsrt_term_heap_capacity;

/**
 * @brief The global term object heap.
 */
static DSRTTermObject **dsrt_term_heap;

/**
 * @brief Initialize the global term object heap.
 */
void dsrt_term_heap_init(void);

/**
 * @brief Uninitialize the global term object heap.
 */
void dsrt_term_heap_exit(void);

#ifdef __cplusplus
}
#endif
