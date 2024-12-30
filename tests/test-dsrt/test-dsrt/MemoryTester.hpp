/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file MemoryTester.hpp
 * @author Gianmarco Lenzi
 * @brief Header for memory tester class.
 */

#pragma once
#include "common.hpp"

namespace TestDSRT::TestMemory {
    /**
     * @brief Class for DSRT memory tester.
     */
    class MemoryTester final : public ModuleTester {
        protected:
            [[nodiscard]] std::vector<UnitTester *> get_tests() const override {
                return {
                    new SimpleSingle()
                };
            }

            [[nodiscard]] std::string get_module_name() const override {
                return module_name;
            }

            [[nodiscard]] std::string get_component_name() const override {
                return component_name;
            }
    };

} // TestDSRT::TestMemory
