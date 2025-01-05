/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file ComponentTester.hpp
 * @author Gianmarco Lenzi
 * @brief Header for component tester class.
 */

#pragma once
#include "common.hpp"

#include "Results.hpp"

namespace TesterLib {
    /**
     * @brief Base class for component testers.
     */
    class ComponentTester {
        protected:
            /**
             * @brief The results of the component tests.
             */
            Results results;

            /**
             * @brief The information about the component tests.
             */
            TestInfo test_info;

            /**
             * @brief Gets the list of tests for the component.
             * @return The list of tests.
             */
            virtual TestList get_tests() const {
                return {};
            }

            /**
             * @brief Constructor.
             * @param test_name_list The list of test names for the component.
             * @details This constructor initializes the results and test information.
             */
            explicit ComponentTester(TestNameList test_name_list) : results(test_name_list),
                                                                    test_info(std::move(test_name_list)) {}
        public:
            /**
             * @brief Virtual destructor for the ComponentTester class.
             * @details Ensures proper cleanup of derived classes.
             */
            virtual ~ComponentTester() = default;

            /**
             * @brief Gets the name of the component.
             * @return The name of the component.
             */
            virtual const ComponentName &get_name() const = 0;

            /**
             * @brief Gets the test information for the component.
             * @return The test information.
             */
            [[nodiscard]] const TestInfo &get_test_info() const { return test_info; }

            /**
             * @brief Gets the results of the component tests.
             * @return The results of the component tests.
             */
            [[nodiscard]] const Results &get_results() const { return results; }

            /**
             * @brief Runs the tests in this component and logs the results.
             */
            void run_tests();
    };
} // TesterLib
