/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file DsrtTester.hpp
 * @author Gianmarco Lenzi
 * @brief Header for DSRT tester class.
 */

#pragma once
#include "common.hpp"
#include "test-abi/common.hpp"
#include "test-memory/common.hpp"

namespace TestDSRT {
    /**
     * @brief Class for DSRT tester.
     */
    class DSRTTester final : public ComponentTester {
        private:
            inline static const TestList tests = {
                {TestMemory::module_name, TestMemory::tests},
                {TestABI::module_name, TestABI::tests}
            };
        protected:
            TestList get_tests() const override {
                return tests;
            }
        public:
            DSRTTester() : ComponentTester({}) {
                TestNameList test_name_list;

                for (const auto &[module_name, module_tests] : get_tests()) {
                    for (const auto &test_name: module_tests | std::views::keys) {
                        test_name_list[module_name].push_back(test_name);
                    }
                }

                this->results = Results{test_name_list};
                this->test_info = TestInfo{std::move(test_name_list)};
            }

            const String &get_name() const override { return component_name; }
    };
} // TestDSRT
