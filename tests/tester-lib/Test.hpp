/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file Test.hpp
 * @author Gianmarco Lenzi
 * @brief Header for unit test class.
 */

#pragma once
#include "common.hpp"
#include "Tester.hpp"

namespace TesterLib {
    /**
     * @brief Class for unit tests.
     */
    class Test : public Tester {
        private:
            /**
             * @brief The name of the test.
             */
            std::string name;

            /**
             * @brief The name of the module.
             */
            std::string module_name;

            /**
             * @brief The name of the component.
             */
            std::string component_name;
        public:
            std::string get_name() const override;
            std::string get_full_name() const override;
    };

} // TesterLib
