/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file ABITester.hpp
 * @author Gianmarco Lenzi
 * @brief 
 */

#pragma once
#include "common.hpp"

namespace TestDSRT::TestABI {

    class ABITester final : public ModuleTester {
        protected:
            [[nodiscard]] std::vector<UnitTester *> get_tests() const override {
                return {
                    new PackUnpack()
                };
            }

            [[nodiscard]] std::string get_module_name() const override { return module_name; }

            [[nodiscard]] std::string get_component_name() const override { return component_name; }
    };

} // TestDSRT
