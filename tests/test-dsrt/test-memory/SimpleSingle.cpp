/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file SimpleSingle.cpp
 * @author Gianmarco Lenzi
 * @brief 
 */

#include "SimpleSingle.hpp"
#include "../../../src/dsrt/dsrt_memory.h"

namespace TestDSRT::TestMemory {
    void SimpleSingle::run() const {
        // Create a simple allocator
        constexpr DSRTSimpleAllocator allocator = {
            .is_array = false,
            .descriptor = {
                .size_of = sizeof(int)
            }
        };

        // Create a simple object
        const DSRTSimpleObject object = dsrt_simple_new(allocator);

        // Initialize the object
        *static_cast<int *>(object.obj) = 42;

        // Check the object
        if (*static_cast<int *>(object.obj) != 42) {
            this->fail("The object was not initialized correctly, with a value of "
                + std::to_string(*static_cast<int *>(object.obj))
                + ", but should have been 42.");
        }

        // Delete the object
        dsrt_simple_del(object);
    }
} // TestDSRT::TestMemory