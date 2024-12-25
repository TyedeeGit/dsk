/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file main.cpp
 * @author Gianmarco Lenzi
 * @brief Entry point for the DSRT tester.
 */

#include "main.hpp"


int main() {
    // Initialize the tester
    const TestDSRT::DSRTTester tester;

    // Run the tests
    const TesterLib::ComponentResults results = tester.test_all();

    // Return the results
    return results.get_passed_tests() == results.get_total_tests() ? 0 : 1;
}
