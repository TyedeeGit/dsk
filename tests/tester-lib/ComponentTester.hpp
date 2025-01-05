/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
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
            Results results;
            TestInfo test_info;

            virtual TestList get_tests() const {
                return {};
            }

            explicit ComponentTester(TestNameList test_name_list) : results(test_name_list),
                                                                    test_info(std::move(test_name_list)) {}
        public:
            virtual ~ComponentTester() = default;

            virtual const ComponentName &get_name() const = 0;
            [[nodiscard]] const TestInfo &get_test_info() const { return test_info; }
            [[nodiscard]] const Results &get_results() const { return results; }

            void run_tests();
    };
} // TesterLib
