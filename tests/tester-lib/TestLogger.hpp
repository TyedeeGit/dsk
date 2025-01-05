/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file TestLogger.hpp
 * @author Gianmarco Lenzi
 * @brief Header for test logger class.
 */

#pragma once
#include <utility>

#include "Results.hpp"

#include "logging.hpp"

namespace TesterLib {
    /**
     * @brief Class for logging test results.
     */
    class TestLogger {
        private:
            /**
             * @brief The name of the component.
             */
            ComponentName component_name;

            /**
             * @brief The name of the module.
             */
            ModuleName module_name;

            /**
             * @brief The name of the test.
             */
            TestName test_name;

            /**
             * @brief The component results.
             *
             */
            Results &results;
        public:
            /**
             * @brief Constructor.
             * @param component_name The name of the component.
             * @param module_name The name of the module.
             * @param test_name The name of the test.
             * @param results The component results.
             */
            TestLogger(ComponentName component_name, ModuleName module_name, TestName test_name,
                       Results &results) : component_name(std::move(component_name)),
                                           module_name(std::move(module_name)),
                                           test_name(std::move(test_name)), results(results) {}

            /**
             * @brief Gets the name of the component.
             * @return The name of the component.
             */
            [[nodiscard]] const ComponentName &get_component_name() const { return component_name; }

            /**
             * @brief Gets the name of the module.
             * @return The name of the module.
             */
            [[nodiscard]] const ModuleName &get_module_name() const { return module_name; }

            /**
             * @brief Gets the name of the test.
             * @return The name of the test.
             */
            [[nodiscard]] const TestName &get_test_name() const { return test_name; }

            /**
             * @brief Gets the component results.
             * @return The component results.
             */
            [[nodiscard]] const Results &get_results() const { return results; }

            /**
             * @brief Gets the scope of the test.
             * @return The scope of the test.
             */
            [[nodiscard]] String get_scope() const { return component_name + "." + module_name + "." + test_name; }

            /**
             * @brief Logs a fail message and updates the component results.
             * @param message The message to log.
             */
            void fail(Message message) const {
                Logging::log_fail(get_scope(), message);
                results.failure_messages[{module_name, test_name}] = std::move(message);
                results.update_totals();
            }

            /**
             * @brief Logs a warn message and updates the component results.
             * @param message The message to log.
             */
            void warn(Message message) const {
                Logging::log_warn(get_scope(), message);
                results.warning_messages[{module_name, test_name}].push_back(std::move(message));
                results.update_totals();
            }

            /**
             * @brief Logs a pass message and updates the component results.
             * @details Clears the failure messages for the test and updates the total number of failed tests.
             */
            void pass() const {
                Logging::log_pass(get_scope(), "Test passed.");
                results.failure_messages[{module_name, test_name}] = {};
                results.update_totals();
            }
    };

} // TesterLib
