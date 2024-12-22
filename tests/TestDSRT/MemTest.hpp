/*
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file tests/Tests/MemTest.hpp
 * @author Gianmarco Lenzi
 * @brief Memory management tests header.
 */

#pragma once

#include "common.hpp"
#include "memory.h"

namespace MemTest {
    /*
     * @brief Test memory management of a simple single object.
     * @return True if the test passed, false otherwise.
     */
    bool test_simple_single();

    /*
     * @brief Test memory management of a simple array object.
     * @return True if the test passed, false otherwise.
     */
    bool test_simple_array();

    /*
     * @brief Run all tests in MemTest.
     * @return True if all tests passed, false otherwise.
     */
    bool test_all();
}