/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file array_copy.cpp
 * @author Gianmarco Lenzi
 * @brief 
 */

#include "common.hpp"
#include "../../../src/dsrt/abi.h"

namespace TestDSRT::TestABI {
    void array_copy(const TestLogger &logger) {
        // Create test values.
        constexpr DSRTIndex start = 1, end = 4;
        constexpr DSRTNat32 test_vals[5] = {1, 2, 3, 4, 5};

        // Create the source buffer.
        // ReSharper disable once CppCStyleCast
        const DSRTBuffer src = {sizeof(test_vals), (char *) test_vals};

        // Create the destination buffer.
        const DSRTBuffer dest = dsrt_alloc_buffer(sizeof(DSRTNat32) * 3);
        // Create the destination seeker.
        DSRTSeeker dest_seeker = dsrt_seeker_new(dest);

        // Copy the section from the source buffer to the destination buffer.
        dsrt_copy_section_from_array(&dest_seeker, src, sizeof(DSRTNat32), start, end);

        // Check the copied data.
        for (DSRTIndex i = 0; i < end - start; i++) {
            const DSRTNat32 expected = test_vals[start + i];
            if (const DSRTNat32 actual = dsrt_unpack_nat32(&dest_seeker); expected != actual) {
                logger.fail("Failed to copy section from array, expected " + std::to_string(expected) + " but got " +
                     std::to_string(actual) + " at index " + std::to_string(i) + ".");
                return;
            }
        }

        // Free the destination buffer.
        dsrt_free_buffer(dest);

        logger.pass();
    }

}
