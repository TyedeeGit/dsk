/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file DsrtTester.hpp
 * @author Gianmarco Lenzi
 * @brief Header for DSRT tester class.
 */

#pragma once
#include "common.hpp"
#include "test-dsrt/all.hpp"

namespace TestDSRT {
    /**
     * @brief Class for DSRT tester.
     */
    class DSRTTester final : public ComponentTester {
        protected:
            [[nodiscard]] std::vector<ModuleTester *> get_modules() const override {
                return {
                    new TestMemory::MemoryTester()
                };
            }

            [[nodiscard]] std::string get_component_name() const override {
                return component_name;
            }
    };
} // TestDSRT
