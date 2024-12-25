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
            std::vector<UnitTester *> get_tests() const override {
                return {
                    new SimpleSingle()
                };
            }

            std::string get_module_name() const override {
                return module_name;
            }

            std::string get_component_name() const override {
                return component_name;
            }
    };

} // TestDSRT::TestMemory
