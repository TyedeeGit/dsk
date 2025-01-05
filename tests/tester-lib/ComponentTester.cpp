/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file ComponentTester.cpp
 * @author Gianmarco Lenzi
 * @brief Implementation of the component tester class.
 */

#include "ComponentTester.hpp"
#include "TestLogger.hpp"

#include <iomanip>
#include <sstream>

namespace TesterLib {
    /**
     * @brief Runs the tests in this component and logs the results.
     */
    void ComponentTester::run_tests() {
        // Count total tests and modules
        const unsigned total_tests = test_info.get_global_total();
        const unsigned total_modules = test_info.get_total_modules();

        // Log that we are running the tests in this component
        Logging::log_info(get_name(), "Running " + std::to_string(total_tests) + " component test(s) across " + std::to_string(total_modules) + " module(s)...");

        for (const auto &[module_name, module_test_names] : test_info.get_tests()) {
            // Define the module scope and count total module tests
            const auto module_scope = get_name() + "." + module_name;
            const unsigned total_module_tests = test_info.get_module_total(module_name);

            // Log that we are running the tests in this module
            Logging::log_info(module_scope, "Running " + std::to_string(total_module_tests) + " module test(s)...");

            for (const auto &test_name : module_test_names) {
                // Define the test scope
                auto test_scope = module_scope + "."; test_scope += test_name;

                // Log that we are running this test
                Logging::log_info(test_scope, "Running test...");

                // Run the test
                get_tests()[module_name][test_name]({get_name(), module_name, test_name, results});

                if (const unsigned total_test_warnings = results.get_total_test_warnings(module_name, test_name); total_test_warnings > 0) {
                    // If the test finished with warnings, log that.
                    Logging::log_info(test_scope, "Test finished with " + std::to_string(total_test_warnings) + " warning(s).");
                } else {
                    // Otherwise, log that the test finished with no warnings.
                    Logging::log_info(test_scope, "Test finished with no warnings.");
                }
            }

            // Get the total module failures
            const unsigned total_module_failures = results.get_total_module_failures(module_name);

            if (total_module_failures > 0) {
                // Create a failure message stream
                std::stringstream failure_message_stream{""};

                // ```
                // Module finished with {total_module_failures} failures out of {total_module_tests} test(s). :(
                // ```
                failure_message_stream << "Module finished with " << total_module_failures << " failures out of " <<
                    total_module_tests << " test(s). :(";

                // Log the failure message
                Logging::log_fail(module_scope, failure_message_stream.str());
            } else {
                // Log that all tests in the module passed
                Logging::log_pass(module_scope, "All tests in module passed! :D");
            }

            // Create a pass rate stream
            std::stringstream module_pass_rate_stream{""};

            // Get the pass rate
            const double pass_rate = static_cast<double>(total_module_tests - total_module_failures) / total_module_tests * 100.0;

            // ```
            // {pass_rate}%({total_module_tests - total_module_failures}/{total_module_tests}) pass rate.
            // ```
            module_pass_rate_stream << std::fixed << std::setprecision(1) << pass_rate << "%(" << total_module_tests - total_module_failures << "/" << total_module_tests << ") pass rate.";

            // Log the pass rate
            Logging::log_info(module_scope, module_pass_rate_stream.str());

            if (const unsigned total_module_warnings = results.get_total_module_warnings(module_name); total_module_warnings > 0) {
                // If the module finished with warnings, log that.
                Logging::log_info(module_scope, "Module finished with " + std::to_string(total_module_warnings) + " warning(s).");
            } else {
                // Otherwise, log that the module finished with no warnings.
                Logging::log_info(module_scope, "Module finished with no warnings.");
            }
        }

        // Count total failures
        const unsigned total_failures = results.get_total_failures();

        if (total_failures > 0) {
            // Create a failure message stream
            std::stringstream failure_message_stream{""};

            // ```
            // Component finished with {total_failures} failed test(s) out of {total_tests} test(s) and
            // {results.get_total_failed_modules()} failed module(s) out of {total_modules} modules(s).
            // ```
            failure_message_stream << "Component finished with " << total_failures << " failed test(s) out of " <<
                    total_tests << " test(s) and " << results.get_total_failed_modules() << " failed module(s) out of " <<
                        total_modules << " modules(s). :(";

            // Log the failure message
            Logging::log_fail(get_name(), failure_message_stream.str());
        } else {
            // Log that all tests in the component passed
            Logging::log_pass(get_name(), "All tests in component passed! :D :D :D");
        }

        // Create a pass rate stream
        std::stringstream component_pass_rate_stream{""};

        // Calculate the test and module pass rate
        const double test_pass_rate = static_cast<double>(total_tests - total_failures) / total_tests * 100.0;
        const double module_pass_rate = static_cast<double>(total_modules - results.get_total_failed_modules()) /
                                        total_modules * 100.0;

        // ```
        // Component finished with {total_failures} failed test(s) out of {total_tests} test(s) and
        // {results.get_total_failed_modules()} failed module(s) out of {total_modules} modules(s).
        // {test_pass_rate}%({total_tests - total_failures}/{total_tests}) test pass rate and
        // {module_pass_rate}%({total_modules - results.get_total_failed_modules()}/{total_modules}) module pass rate.
        // ```
        component_pass_rate_stream << std::fixed << std::setprecision(1) << test_pass_rate << "%(" <<
                            total_tests - total_failures << "/" << total_tests << ") test pass rate and " <<
                                module_pass_rate << "%(" << total_modules - results.get_total_failed_modules() << "/" <<
                                    total_modules << ") module pass rate.";

        // Log the pass rates
        Logging::log_info(get_name(), component_pass_rate_stream.str());

        if (const unsigned total_warnings = results.get_total_warnings(); total_warnings > 0) {
            // If the component finished with warnings, log that.
            Logging::log_info(get_name(), "Component finished with " + std::to_string(total_warnings) + " warning(s).");
        } else {
            // Otherwise, log that the component finished with no warnings.
            Logging::log_info(get_name(), "Component finished with no warnings.");
        }
    }
} // TesterLib