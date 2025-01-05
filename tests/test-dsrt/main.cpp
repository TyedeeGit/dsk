/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file main.cpp
 * @author Gianmarco Lenzi
 * @brief Entry point for the DSRT tester.
 */

#include "main.hpp"
#include "common.hpp"
#include "../../src/dsrt/dsrt_memory.h"
#include "../../src/dsrt/err.h"

#include "DSRTTester.hpp"


int main() {
    // Initialize DSRT.
    dsrt_init();

    auto tester = TestDSRT::DSRTTester();
    tester.run_tests();

    // Safely exit.
    dsrt_exit(tester.get_results().did_pass() ? 0 : 1);
}
