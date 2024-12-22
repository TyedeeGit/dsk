/*
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file src/dsrt_memory.c
 * @author Gianmarco Lenzi
 * @brief Memory management functions for the DSRT library.
 */

#include "dsrt_memory.h"

DSRTSize dsrt_simple_get_alloc_size(DSRTSimpleAllocator allocator) {
    return allocator.is_array ? allocator.descriptor.array_of.num * allocator.descriptor.array_of.size : allocator.descriptor.size_of;
}

DSRTSize dsrt_simple_get_obj_size(DSRTSimpleObject obj) {
    return dsrt_simple_get_alloc_size(obj.allocator);
}

void dsrt_simple_heap_init(void) {
    // Initialize the heap with a size of 0 and capacity of 1.
    dsrt_simple_heap_size = 0;
    dsrt_simple_heap_capacity = 1;
    dsrt_simple_heap = malloc(sizeof(DSRTSimpleObject *));
}

DSRTSimpleObject dsrt_simple_new(DSRTSimpleAllocator allocator) {
    // If the heap is full, double its capacity.
    if (dsrt_simple_heap_size == dsrt_simple_heap_capacity) {
        // Double the capacity and reallocate a new heap.
        dsrt_simple_heap_capacity *= 2;
        DSRTSimpleObject **new_heap = realloc(dsrt_simple_heap, sizeof(DSRTSimpleObject *) * dsrt_simple_heap_capacity);

        // If the reallocation fails, print an error message and exit.
        if (new_heap == NULL) {
            fprintf(stderr, "DTL runtime error: Out of memory\n");
            dsrt_exit();
            exit(1);
        }

        // Update the heap pointer.
        dsrt_simple_heap = new_heap;
    }

    // Push the new object onto the heap, initialize it, increment the heap size, and return the object.
    dsrt_simple_heap[dsrt_simple_heap_size] = malloc(sizeof(DSRTSimpleObject));
    DSRTSimpleObject *object = dsrt_simple_heap[dsrt_simple_heap_size];

    DSRTSize size = dsrt_simple_get_alloc_size(allocator);
    object->ind = dsrt_simple_heap_size;
    object->obj = malloc(size);
    object->allocator = allocator;
    memset(object->obj, 0, size);

    dsrt_simple_heap_size++;
    return *object;
}

void dsrt_simple_del(DSRTSimpleObject object) {
    // Store all objects after this one in a temporary buffer.
    DSRTSimpleObject *later_objects = calloc(dsrt_simple_heap_size - object.ind + 1, sizeof(DSRTSimpleObject *));
    // If the allocation fails, print an error message and exit.
    if (later_objects == NULL) {
        fprintf(stderr, "DTL runtime error: Out of memory\n");
        dsrt_exit();
        exit(1);
    }
    // Actually free the object and set its freed flag to true.
    free(object.obj);
    free(dsrt_simple_heap[object.ind]);

    // Copy all objects after this one into the temporary buffer and decrement their indices.
    memccpy(later_objects, dsrt_simple_heap + object.ind + 1, dsrt_simple_heap_size - object.ind + 1, sizeof(DSRTSimpleObject *));
    for (DSRTIndex i = 0; i < dsrt_simple_heap_size - object.ind - 1; i++) {
        later_objects[i].ind--;
    }

    // Copy the temporary buffer into the heap and free it.
    memccpy(dsrt_simple_heap + object.ind, later_objects, dsrt_simple_heap_size - object.ind + 1, sizeof(DSRTSimpleObject *));
    free(later_objects);

    // Decrement the heap size.
    dsrt_simple_heap_size--;

    // If the heap is half full, downsize it.
    if (dsrt_simple_heap_size == dsrt_simple_heap_capacity / 2 && dsrt_simple_heap_capacity > 1) {
        // Reallocate a new heap with half the capacity.
        DSRTSimpleObject **new_heap = realloc(dsrt_simple_heap, sizeof(DSRTSimpleObject *) * dsrt_simple_heap_size);

        // If the reallocation fails, print an error message and exit.
        if (new_heap == NULL) {
            fprintf(stderr, "DTL runtime error: Out of memory\n");
            dsrt_exit();
            exit(1);
        }

        // Update the heap pointer and heap capacity.
        dsrt_simple_heap = new_heap;
        dsrt_simple_heap_capacity = dsrt_simple_heap_size > 0 ? dsrt_simple_heap_size : 1;
    }
}

void dsrt_simple_heap_exit(void) {
    // Free all objects in the heap if there are any.
    if (dsrt_simple_heap_size > 0) {
        for (DSRTIndex i = dsrt_simple_heap_size - 1; i > 0; i--) {
            free(dsrt_simple_heap[i]->obj);
        }
    }

    // Free the heap.
    free(dsrt_simple_heap);
}

void dsrt_term_heap_init(void) {
    // Initialize the heap with a size of 0 and capacity of 1.
    dsrt_term_heap_size = 0;
    dsrt_term_heap_capacity = 1;
    dsrt_term_heap = malloc(sizeof(DSRTTermObject));
}

// TODO: Implement term constructor.

// TODO: Implement term deleter.

void dsrt_term_heap_exit(void) {
    // Free the heap.
    // TODO: Free all objects in the heap, must implement a free function first.
    free(dsrt_term_heap);
}