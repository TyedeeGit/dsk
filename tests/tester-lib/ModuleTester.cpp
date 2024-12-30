/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file ModuleTester.cpp
 * @author Gianmarco Lenzi
 * @brief Implementation of the module tester class.
 */

#include "ModuleTester.hpp"
#include "logging.hpp"

namespace TesterLib {
    ModuleResults ModuleTester::test_all() const {
        // Log amount of tests.
        Logging::log_info(this->get_full_name(), "Total module tests: " + std::to_string(this->get_total_tests()));

        // Log the start of the tests.
        Logging::log_info(this->get_full_name(), "Running module tests...");

        // Initialize the results.
        ModuleResults results;

        for (const auto &test : this->get_tests()) {
            // Add the results.
            results.add_test(test->get_name(), test->test());

            // Delete the test.
            delete test;
        }

        // Log the results.
        if (results.get_passed() == results.get_total()) {
            if (results.get_warnings().empty()) {
                // If there are no warnings, celebrate.
                Logging::log_pass(this->get_full_name(), "Module passed with no warnings. :D");
            } else {
                // Otherwise, log that the module passed with warnings.
                Logging::log_pass(this->get_full_name(),
                                  "Module passed with "
                                  + std::to_string(results.get_warnings().size())
                                  + " warning(s). :)");
            }
        } else {
            if (results.get_warnings().empty()) {
                // If there are no warnings, log that the module failed with no warnings.
                Logging::log_fail(this->get_full_name(), "Module failed with no warnings. :(");
            } else {
                // Otherwise, log that the module failed with warnings.
                Logging::log_fail(this->get_full_name(),
                    "Module failed with "
                    + std::to_string(results.get_warnings().size())
                    + " warning(s). :(");
            }
        }

        // Return the results.
        return results;
    }
} // TesterLib