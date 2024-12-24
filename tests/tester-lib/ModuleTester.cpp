/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file ModuleTester.cpp
 * @author Gianmarco Lenzi
 * @brief Implementation of the module tester class.
 */

#include "ModuleTester.hpp"

namespace TesterLib {
    ModuleResults ModuleTester::test_all() const {
        // Log the start of the tests.
        Logging::log_info(this->get_full_name(), "Running tests...");

        // Initialize the results.
        ModuleResults results;

        // Get the tests.
        const auto tests = this->get_tests();

        for (const auto &test : tests) {
            // Run the test.
            auto test_results = test.test();

            // Add the results.
            results.add_test(test.get_name(), test_results);
        }

        // TODO: Log the results.

        // Return the results.
        return results;
    }
} // TesterLib