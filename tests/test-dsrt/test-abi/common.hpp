/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file common.hpp
 * @author Gianmarco Lenzi
 * @brief Common header for the ABI tester.
 */

#pragma once
#include "../common.hpp"

namespace TestDSRT::TestABI {
    /**
     * @brief The named of the DSRT ABI tester module.
     */
    const String module_name = "abi";

    /**
     * @brief Test the packing and unpacking functionality.
     *
     * @details This function tests the packing and unpacking of various data types
     * (Int8, Int16, Int32, Int64) to ensure that the packed data can be
     * correctly unpacked to retrieve the original values.
     *
     * @param logger The logger used to record test results.
     */
    void pack_unpack(const TestLogger &logger);

    /**
     * @brief Test the copying of a section of an array to another.
     *
     * @details This function tests the copying of a section of an array to another
     * to ensure that the section is correctly copied.
     *
     * @param logger The logger used to record test results.
     */
    void array_copy(const TestLogger &logger);

    /**
     * @brief Test the ctype functions.
     *
     * @details This function tests size, packing, and unpacking of ctypes.
     *
     * @param logger The logger used to record test results.
     */
    void ctype(const TestLogger &logger);

    inline ModuleTests tests = {
        {"pack_unpack", pack_unpack},
        {"array_copy", array_copy},
        {"ctype", ctype},
    };
} // TestDSRT::TestABI