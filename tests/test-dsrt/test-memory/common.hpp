/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file common.hpp
 * @author Gianmarco Lenzi
 * @brief Common header for the DSRT memory tester module.
 */

#pragma once
#include "../common.hpp"

namespace TestDSRT::TestMemory {
    const ModuleName module_name = "memory";

    void simple_single(const TestLogger &logger);

    void simple_array(const TestLogger &logger);

    inline ModuleTests tests = {
        {"simple_single", &simple_single}
    };
} // TestDSRT::TestMemory
