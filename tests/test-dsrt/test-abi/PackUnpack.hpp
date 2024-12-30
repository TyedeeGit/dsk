/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file PackUnpack.hpp
 * @author Gianmarco Lenzi
 * @brief 
 */

#pragma once
#include "common.hpp"

namespace TestDSRT::TestABI {

    class PackUnpack final : public UnitTester {
        private:
            void run() const override;

            std::string get_test_name() const override { return "pack_unpack"; }

            std::string get_module_name() const override { return module_name; }

            std::string get_component_name() const override { return component_name; }
        public:
            PackUnpack() : UnitTester() {}
    };

}
