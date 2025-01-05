/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file common.hpp
 * @author Gianmarco Lenzi
 * @brief Common header for the ABI tester.
 */

#pragma once
#include "../common.hpp"

namespace TestDSRT::TestABI {
    const String module_name = "abi";

    void pack_unpack(const TestLogger &logger);

    void array_copy(const TestLogger &logger);

    inline ModuleTests tests = {
        {"pack_unpack", &pack_unpack},
        {"array_copy", &array_copy}
    };
} // TestDSRT::TestABI