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

        for (const auto &test : this->get_tests()) {
            // Add the results.
            results.add_test(test.get_name(), test.test());
        }

        // TODO: Log the results.

        // Return the results.
        return results;
    }
} // TesterLib