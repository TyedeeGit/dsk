/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file TestInfo.hpp
 * @author Gianmarco Lenzi
 * @brief Header for test information class.
 */

#pragma once
#include "common.hpp"

namespace TesterLib {
    /**
     * @brief Class for storing test information.
     */
    class TestInfo {
        private:
            /**
             * @brief A map of all modules to their tests.
             */
            TestNameList tests;

            /**
             * @brief A map of all modules to their total number of tests.
             */
            Dict<ModuleName, unsigned> module_totals;

            /**
             * @brief The total number of tests.
             */
            unsigned global_total = 0;

            /**
             * @brief Updates the global total number of tests and the module totals.
             */
            void update_totals() {
                // Clear the totals
                module_totals.clear();
                global_total = 0;

                for (auto const &[module_name, module_tests] : tests) {
                    // Update the totals
                    module_totals[module_name] = module_tests.size();
                    global_total += module_tests.size();
                }
            }
        public:
            /**
             * @brief Constructor.
             * @param tests The list of tests.
             */
            explicit TestInfo(TestNameList tests = {}) : tests(std::move(tests)) {
                update_totals();
            }

            /**
             * @brief Gets the list of tests.
             * @return The list of tests.
             */
            [[nodiscard]] TestNameList get_tests() const { return tests; }

            /**
             * @brief Gets the total number of tests for each module.
             * @return The total number of tests for each module.
             */
            [[nodiscard]] const Dict<ModuleName, unsigned> &get_module_totals() const { return module_totals; }

            /**
             * @brief Gets the total number of tests in @code module_name@endcode.
             * @param module_name The name of the module.
             * @return The total number of tests in @code module_name@endcode.
             */
            [[nodiscard]] unsigned get_module_total(const ModuleName &module_name) const { return module_totals.at(module_name); }

            /**
             * @brief Gets the total number of tests.
             * @return The total number of tests.
             */
            [[nodiscard]] unsigned get_global_total() const { return global_total; }

            /**
             * @brief Gets the total number of modules.
             * @return The total number of modules.
             */
            [[nodiscard]] unsigned get_total_modules() const { return tests.size(); }
    };

} // TesterLib
