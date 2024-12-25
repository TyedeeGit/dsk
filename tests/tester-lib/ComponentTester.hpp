/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file ComponentTester.hpp
 * @author Gianmarco Lenzi
 * @brief Header for component tester class.
 */

#pragma once
#include "common.hpp"
#include "logging.hpp"

#include "ComponentResults.hpp"
#include "Tester.hpp"
#include "ModuleTester.hpp"

namespace TesterLib {
    /**
     * @brief Base class for component testers.
     */
    class ComponentTester : public Tester {
        protected:
            /**
             * @brief Gets the modules in this component.
             * @return The modules in this component.
             */
            virtual std::vector<ModuleTester *> get_modules() const = 0;

            /**
             * @brief Gets the name of the component.
             * @return The name of the component.
             */
            virtual std::string get_component_name() const = 0;
        public:
            /**
             * @brief Constructor.
             */
            ComponentTester() = default;

            /**
             * @brief Gets the fully qualified name of the component.
             * @return The fully qualified name of the component.
             */
            std::string get_full_name() const override {
                return this->get_component_name();
            }
            /**
             * @brief Gets the name of the component.
             * @return The name of the component.
             */
            std::string get_name() const override {
                return this->get_component_name();
            }

            /**
             * @brief Runs all the tests in all the modules in this component.
             * @return The results of all the tests.
             */
            ComponentResults test_all() const;
    };
} // TesterLib
