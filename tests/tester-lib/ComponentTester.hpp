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
            virtual std::vector<ModuleTester> get_modules() const = 0;
        public:
            /**
             * @brief Constructor.
             */
            ComponentTester() = default;

            /**
             * @brief Runs all the tests in all the modules in this component.
             * @return The results of all the tests.
             */
            ComponentResults test_all() const;
    };
} // TesterLib
