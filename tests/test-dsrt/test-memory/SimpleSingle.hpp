/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file SimpleSingle.hpp
 * @author Gianmarco Lenzi
 * @brief 
 */

#pragma once
#include "common.hpp"

namespace TestDSRT::TestMemory {
    /**
     * @brief Test DSRT memory management of a simple single object.
     */
    class SimpleSingle final : public UnitTester {
        private:
            void run() const override;

            std::string get_test_name() const override { return "simple_single"; }

            std::string get_module_name() const override { return module_name; }

            std::string get_component_name() const override { return component_name; }
        public:
            /**
             * @brief Constructor.
             */
            SimpleSingle() : UnitTester() {}
    };
} // TestDSRT::TestMemory
