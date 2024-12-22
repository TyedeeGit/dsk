/*
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file tests/main.cpp
 * @author Gianmarco Lenzi
 * @brief Entry point for the tests.
 */

#include "main.hpp"

bool test_all() {
    // Begin logging.
    Logging::log_begin();

    // Run the tests.
    MemTest::test_all();

    // Log the results.
    Logging::log_results();
    return !Logging::failed;
}

int main() {
    dsrt_init();
    bool passed = test_all();
    dsrt_exit();
    return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
