/*
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file tests/Tests/MemTest.cpp
 * @author Gianmarco Lenzi
 * @brief Memory management tests.
 */

#include "MemTest.hpp"

namespace MemTest {
    bool test_simple_single() {
        Logging::log_test_begin("MemTest", "simple_single_object");

        // Create a simple single object allocator.
        DSRTSimpleAllocator allocator_single = {
                .is_array = false,
                .descriptor = {
                        .size_of = sizeof(int)
                }
        };

        // Create a simple single object.
        DSRTSimpleObject simple_single_object = dsrt_simple_new(allocator_single);

        // Set the value of the simple single object.
        *(int *) simple_single_object.obj = 42;

        // Check the value of the simple single object.
        if (*(int *) simple_single_object.obj != 42) {
            Logging::log_test_fail("MemTest", "simple_single_object", "Failed to initialize the simple single object.");
            return false;
        }

        // Destroy the simple single object.
        dsrt_simple_del(simple_single_object);

        // Success.
        Logging::log_test_pass("MemTest", "simple_single_object");
        return true;
    }

    bool test_simple_array() {
        Logging::log_test_begin("MemTest", "simple_array_object");

        const size_t num = 5;

        // Create test values.
        int test_values[num] = {1, 2, 3, 4, 5};

        // Create a simple array object allocator.
        DSRTSimpleAllocator allocator_array = {
                .is_array = true,
                .descriptor = {
                        .array_of = {
                                .num = num,
                                .size = sizeof(int),
                        }
                }
        };

        // Create a simple array object.
        DSRTSimpleObject simple_array_object = dsrt_simple_new(allocator_array);

        // Set the value of the simple array object.
        memcpy(simple_array_object.obj, test_values, sizeof(int) * num);

        // Check the value of the simple array object.
        if (memcmp(simple_array_object.obj, test_values, sizeof(int) * num) != 0) {
            Logging::log_test_fail("MemTest", "simple_array_object", "Failed to initialize the simple array object.");
            return false;
        }

        // Destroy the simple array object.
        dsrt_simple_del(simple_array_object);

        // Success.
        Logging::log_test_pass("MemTest", "simple_array_object");
        return true;
    }

    bool test_all() {
        Logging::log_module_begin("MemTest");

        // Run the tests.
        bool success = test_simple_single()
                    && test_simple_array();

        // Log the results.
        if (success) {
            Logging::log_module_pass("MemTest");
        } else {
            Logging::log_module_fail("MemTest");
        }

        // Return the result.
        return success;
    }
}
