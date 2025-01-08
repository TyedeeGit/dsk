/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file ctype.cpp
 * @author Gianmarco Lenzi
 * @brief Implementation of the ctype test.
 */
#include "common.hpp"

#include "../../../src/dsrt/abi.h"

namespace TestDSRT::TestABI {
    void ctype(const TestLogger &logger) {
        const DSRTCTypeDescriptor simple_desc = DSRT_INT32;

        constexpr DSRTSize expected_simple_desc_size = sizeof(DSRTInt32);

        if (dsrt_get_ctype_descriptor_size(DSRT_INT32) != expected_simple_desc_size) {
            logger.fail("Failed to get ctype descriptor size, expected " + std::to_string(expected_simple_desc_size) +
                        " but got " + std::to_string(dsrt_get_ctype_descriptor_size(simple_desc)) + ".");
            return;
        }

        // ReSharper disable once CppVariableCanBeMadeConstexpr
        const DSRTCTypeDescriptor array_desc = {
            .type = DSRT_CTYPE_ARRAY,
            .descriptor = {
                .as_array = {
                    .num = 3,
                    .element_type = &DSRT_NAT16
                }
            }
        };

        constexpr DSRTSize expected_array_desc_size = sizeof(DSRTNat16) * 3;

        if (dsrt_get_ctype_descriptor_size(array_desc) != expected_array_desc_size) {
            logger.fail("Failed to get ctype descriptor size, expected " + std::to_string(expected_array_desc_size) +
                        " but got " + std::to_string(dsrt_get_ctype_descriptor_size(array_desc)) + ".");
            return;
        }

        constexpr DSRTSize STRUCT_ELEMENTS = 3;
        const DSRTCTypeDescriptor struct_element_types[STRUCT_ELEMENTS] = {simple_desc, array_desc, array_desc};

        // ReSharper disable once CppVariableCanBeMadeConstexpr
        const DSRTCTypeDescriptor desc = {
            .type = DSRT_CTYPE_STRUCT,
            .descriptor = {
                .as_struct = {
                    .num = STRUCT_ELEMENTS,
                    .element_types = struct_element_types
                }
            }
        };
        constexpr DSRTSize expected_desc_size = expected_simple_desc_size + expected_array_desc_size + expected_array_desc_size;
        if (dsrt_get_ctype_descriptor_size(desc) != expected_desc_size) {
            logger.fail("Failed to get ctype descriptor size, expected " + std::to_string(expected_desc_size) +
                        " but got " + std::to_string(dsrt_get_ctype_descriptor_size(desc)) + ".");
            return;
        }

        constexpr DSRTSize COMPLEX_STRUCT_ELEMENTS = 4;
        constexpr DSRTSize COMPLEX_STRUCT_ARRAY_COUNT = 5;
        const DSRTCTypeDescriptor complex_struct_element_types[COMPLEX_STRUCT_ELEMENTS] = {
            DSRT_INT64,
            DSRT_SIZE,
            {
                .type = DSRT_CTYPE_ARRAY,
                .descriptor = {
                    .as_array = {
                        .num = COMPLEX_STRUCT_ARRAY_COUNT,
                        .element_type = &desc
                    }
                }
            },
            desc
        };

        // ReSharper disable once CppVariableCanBeMadeConstexpr
        const DSRTCTypeDescriptor complex_desc = {
            .type = DSRT_CTYPE_STRUCT,
            .descriptor = {
                .as_struct = {
                    .num = COMPLEX_STRUCT_ELEMENTS,
                    .element_types = complex_struct_element_types
                }
            }
        };

        if (constexpr DSRTSize expected_complex_desc_size =
                    sizeof(DSRTInt64) + sizeof(DSRTSize) + expected_desc_size * COMPLEX_STRUCT_ARRAY_COUNT + expected_desc_size;
            dsrt_get_ctype_descriptor_size(complex_desc) != expected_complex_desc_size) {
            logger.fail("Failed to get ctype descriptor size, expected " + std::to_string(expected_complex_desc_size) +
                        " but got " + std::to_string(dsrt_get_ctype_descriptor_size(desc)) + ".");
            return;
        }

        logger.pass();
    }
} // TestDSRT::TestABI