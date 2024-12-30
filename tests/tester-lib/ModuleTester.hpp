/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file ModuleTester.hpp
 * @author Gianmarco Lenzi
 * @brief Header for module tester class.
 */

#pragma once
#include "common.hpp"

#include "UnitTester.hpp"
#include "ModuleResults.hpp"

namespace TesterLib {
    /**
     * @brief Base class for module testers.
     */
    class ModuleTester : public Tester {
        protected:
            /**
             * @brief Gets the tests in this module.
             * @return The tests in this module.
             */
            [[nodiscard]] virtual std::vector<UnitTester *> get_tests() const = 0;
            /**
             * @brief Gets the name of the module.
             * @return The name of the module.
             */
            [[nodiscard]] virtual std::string get_module_name() const = 0;

            /**
             * @brief Gets the name of the component.
             * @return The name of the component.
             */
            [[nodiscard]] virtual std::string get_component_name() const = 0;
        public:
            /**
             * @brief Constructor.
             */
            ModuleTester() = default;

            /**
             * @brief Gets the full name of the module.
             * @return The full name of the module.
             */
            [[nodiscard]] std::string get_full_name() const override {
                return get_component_name() + "." + get_module_name();
            }

            /**
             * @brief Gets the name of the module.
             * @return The name of the module.
             */
            [[nodiscard]] std::string get_name() const override {
                return get_module_name();
            }

            /**
             * @brief Runs all the tests in this module.
             * @return The results of all the tests in this module.
             * @details This function logs the start of the tests, gets all the tests in the module,
             * and runs each test, logging the start of each test, and adding the results of each
             * test to the module's results.  Finally, it returns the module's results.
             */
            [[nodiscard]] ModuleResults test_all() const;

            /**
             * @brief Gets the total number of tests in the module.
             * @return The total number of tests in the module.
             */
            [[nodiscard]] unsigned get_total_tests() const { return this->get_tests().size(); }
    };

} // TesterLib
