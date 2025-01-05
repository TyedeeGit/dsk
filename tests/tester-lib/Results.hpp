/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file Results.hpp
 * @author Gianmarco Lenzi
 * @brief Header for component results class.
 */

#pragma once
#include <ranges>

#include "common.hpp"

#include "TestInfo.hpp"

namespace TesterLib {
    /**
     * @brief Class for storing component results.
     */
    class Results {
        private:
            /**
             * @brief The information about the tests.
             */
            TestInfo test_info;

            /**
             * @brief The list of failure messages.
             */
            FailureMessages failure_messages;

            /**
             * @brief The list of warning messages.
             */
            WarningMessages warning_messages;

            /**
             * @brief The list of all test warnings.
             */
            Dict<ModuleName, Dict<TestName, unsigned>> total_test_warnings;

            /**
             * @brief The list of failures for each module.
             */
            Dict<ModuleName, unsigned> total_module_failures;

            /**
             * @brief The list of warnings for each module.
             */
            Dict<ModuleName, unsigned> total_module_warnings;

            /**
             * @brief The total number of failed modules.
             */
            unsigned total_failed_modules = 0;

            /**
             * @brief The total number of failed tests.
             */
            unsigned total_failures = 0;

            /**
             * @brief The total number of warnings.
             */
            unsigned total_warnings = 0;

            /**
             * @brief Updates the total number of failed modules and tests.
             */
            void update_totals();

            friend class TestLogger;
        public:
            /**
             * @brief Constructor.
             * @param test_info The information about the tests.
             * @param failure_messages The list of failure messages.
             * @param warning_messages The list of warning messages.
             */
            explicit Results(const TestNameList &test_info, FailureMessages failure_messages = {},
                                      WarningMessages warning_messages = {}) : test_info(TestInfo{test_info}),
                                                                               failure_messages(
                                                                                   std::move(failure_messages)),
                                                                               warning_messages(
                                                                                   std::move(warning_messages)) {
                update_totals();
            }

            /**
             * @brief Gets the information about the tests.
             * @return The information about the tests.
             */
            [[nodiscard]] const TestInfo &get_test_info() const { return test_info; }

            /**
             * @brief Gets the list of failure messages.
             * @return The list of failure messages.
             */
            [[nodiscard]] const FailureMessages &get_failure_messages() const { return failure_messages; }

            /**
             * @brief Gets the list of warning messages.
             * @return The list of warning messages.
             */
            [[nodiscard]] const WarningMessages &get_warning_messages() const { return warning_messages; }

            /**
             * @brief Gets the list of all test warnings.
             * @return The list of all test warnings.
             */
            [[nodiscard]] const Dict<ModuleName, Dict<TestName, unsigned>> &get_total_test_warnings() const {
                return total_test_warnings;
            }

            /**
             * @brief Gets the list of all test warnings for a module.
             * @param module_name The name of the module.
             * @return The list of all test warnings for a module.
             */
            [[nodiscard]] const Dict<TestName, unsigned> &get_total_test_warnings(const ModuleName &module_name) const {
                return total_test_warnings.at(module_name);
            }

            /**
             * @brief Gets the number of warnings for a test.
             * @param module_name The name of the module.
             * @param test_name The name of the test.
             * @return The number of warnings for a test.
             */
            [[nodiscard]] unsigned get_total_test_warnings(const ModuleName &module_name, const TestName &test_name) const {
                return total_test_warnings.at(module_name).at(test_name);
            }

            /**
             * @brief Gets the list of failures for each module.
             * @return The list of failures for each module.
             */
            [[nodiscard]] const Dict<ModuleName, unsigned> &get_total_module_failures() const {
                return total_module_failures;
            }

            /**
             * @brief Gets the total number of failures for a module.
             * @param module_name The name of the module.
             * @return The total number of failures for a module.
             */
            [[nodiscard]] unsigned get_total_module_failures(const ModuleName &module_name) const {
                return total_module_failures.at(module_name);
            }

            /**
             * @brief Gets the list of warnings for each module.
             * @return The list of warnings for each module.
             */
            [[nodiscard]] const Dict<ModuleName, unsigned> &get_total_module_warnings() const {
                return total_module_warnings;
            }

            /**
             * @brief Gets the total number of warnings for a module.
             * @param module_name The name of the module.
             * @return The total number of warnings for a module.
             */
            [[nodiscard]] unsigned get_total_module_warnings(const ModuleName &module_name) const {
                return total_module_warnings.at(module_name);
            }

            /**
             * @brief Gets the total number of failed tests.
             * @return The total number of failed tests.
             */
            [[nodiscard]] unsigned get_total_failures() const { return total_failures; }

            /**
             * @brief Gets the total number of warnings across all modules and tests.
             * @return The total number of warnings.
             */
            [[nodiscard]] unsigned get_total_warnings() const { return total_warnings; }

            /**
             * @brief Gets the total number of modules that failed.
             * @return The total number of modules that failed.
             */
            [[nodiscard]] unsigned get_total_failed_modules() const {
                return total_failed_modules;
            }

            /**
             * @brief Checks if all tests passed.
             * @details Checks if no tests failed and no tests produced warnings.
             * @return Whether all tests passed.
             */
            [[nodiscard]] bool did_pass() const { return total_failures == 0 && total_warnings == 0; }

            /**
             * @brief Checks if all tests in a specific module passed.
             * @details Determines if no tests failed and no warnings were produced in the specified module.
             * @param module_name The name of the module to check.
             * @return Whether all tests in the specified module passed.
             */
            [[nodiscard]] bool did_pass(const ModuleName &module_name) const {
                return total_module_failures.at(module_name) == 0 && total_module_warnings.at(module_name) == 0;
            }
    };

} // TesterLib
