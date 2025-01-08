/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file common.hpp
 * @author Gianmarco Lenzi
 * @brief Common header for the DSRT memory tester module.
 */

#pragma once
#include "../common.hpp"

namespace TestDSRT::TestMemory {
    /**
     * @brief The name of the DSRT memory tester module.
     */
    const ModuleName module_name = "memory";

    /**
     * @brief Tests the DSRT memory management for a simple single object.
     *
     * @details This function creates a simple allocator and a simple object,
     * initializes the object, checks for correct initialization,
     * and then deletes the object.
     *
     * @param logger The logger to record test results.
     */
    void simple_single(const TestLogger &logger);

    /**
     * @brief Tests the DSRT memory management for a simple array of objects.
     *
     * @details This function creates a simple allocator, a simple object array,
     * initializes the objects in the array, checks for correct initialization,
     * and then deletes the object array.
     *
     * @param logger The logger to record test results.
     */
    void simple_array(const TestLogger &logger);

    inline ModuleTests tests = {
        // {"simple_single", &simple_single}
    };
} // TestDSRT::TestMemory
