/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file ComponentTester.cpp
 * @author Gianmarco Lenzi
 * @brief Implementation of the component tester class.
 */

#include "ComponentTester.hpp"
#include <iomanip>
#include <ranges>

#include "logging.hpp"
#include <sstream>

namespace TesterLib {
    ComponentResults ComponentTester::test_all() const {
        // Log amount of modules.
        Logging::log_info(this->get_full_name(), "Total component modules: " + std::to_string(this->get_total_modules()));

        // Log amount of tests.
        Logging::log_info(this->get_full_name(), "Total component tests: " + std::to_string(this->get_total_tests()));

        // Log the start of the tests.
        Logging::log_info(this->get_full_name(), "Running component tests...");

        // Initialize the results.
        ComponentResults results;

        // Run all the modules.
        for (const auto &module : this->get_modules()) {
            results.add_module(module->get_full_name(), module->test_all());

            // Delete the module.
            delete module;
        }

        // Log the end of the tests.
        Logging::log_info(this->get_full_name(), "Component tests completed!");

        if (results.get_passed_modules() == results.get_total_modules()) {
            // If all the modules passed, log a celebration message.
            Logging::log_pass(this->get_full_name(), "All " + std::to_string(results.get_passed_modules()) + " module(s) passed! :D :D :D");
        } else {
            // Otherwise, log an informative failure message.
            std::stringstream failure_message;
            failure_message << std::fixed << std::setprecision(1) << "Only " << 100.0 * results.get_passed_modules() /
                    results.get_total_modules() << "%(" << results.get_passed_modules() << "/" << results.
                    get_total_modules() << ") passed. :(";
            Logging::log_fail(this->get_full_name(), failure_message.str());
        }

        if (results.get_warnings().empty()) {
            // If there are no warnings, log a happy message.
            Logging::log_pass(this->get_full_name(), "No warnings raised! :)");
        } else {
            // Otherwise, log an informative message.
            std::stringstream warning_message;
            unsigned total_warnings = 0;
            unsigned total_tests_with_warnings = 0;
            unsigned total_modules_with_warnings = 0;

            for (const auto &[module_name, module_warnings] : results.get_warnings()) {
                if (!module_warnings.empty()) {
                    // If the module has warnings, add them to the count of modules with warnings.
                    total_modules_with_warnings++;
                }

                for (const auto &test_warnings: module_warnings | std::views::values) {
                    if (!test_warnings.empty()) {
                        // If the test has warnings, add them to the count of tests with warnings.
                        total_tests_with_warnings++;
                    }

                    // Add the number of warnings raised by the test to the total.
                    total_warnings += test_warnings.size();
                }
            }

            warning_message << total_warnings << " warning(s) raised by " << total_tests_with_warnings <<
                    " test(s) across " << total_modules_with_warnings << " module(s).";
            Logging::log_warn(this->get_full_name(), warning_message.str());
        }

        // Return the results.
        return results;
    }

} // TesterLib