/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
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

    // Initialize the tester.
    const TestDSRT::DSRTTester tester;

    // Run the tests
    const TesterLib::ComponentResults results = tester.test_all();

    // Safely exit.
    dsrt_exit(results.get_passed_tests() == results.get_total_tests() ? 0 : 1);
}
