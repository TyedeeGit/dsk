/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file Results.cpp
 * @author Gianmarco Lenzi
 * @brief Implementation of the component results class.
 */
#include "Results.hpp"

namespace TesterLib {
    void Results::update_totals() {
        // Clear the totals
        total_test_warnings.clear();
        total_module_failures.clear();
        total_module_warnings.clear();
        total_failed_modules = 0;
        total_failures = 0;
        total_warnings = 0;

        for (auto const &[module_name, module_tests] : test_info.get_tests()) {
            // Initialize the total module failures
            total_module_failures[module_name] = 0;

            // Whether the module failed
            bool module_failed = false;

            for (auto const &test_name : module_tests) {
                if (failure_messages[{module_name, test_name}].has_value()) {
                    // If the test failed, increment the total module failures, the total failures, and record that the
                    // module failed.
                    total_module_failures[module_name]++;
                    total_failures++;
                    module_failed = true;
                }

                // Calculate the total test warnings
                const auto warning_count = warning_messages[{module_name, test_name}].size();

                // Record the total test warnings
                total_test_warnings[module_name][test_name] = warning_count;
                total_module_warnings[module_name] += warning_count;
                total_warnings += warning_count;
            }

            if (module_failed) {
                // If the module failed, increment the total failed modules.
                total_failed_modules++;
            }
        }
    }
} // namespace TesterLib