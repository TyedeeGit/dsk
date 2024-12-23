/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file Test.hpp
 * @author Gianmarco Lenzi
 * @brief Header for unit test class.
 */

#pragma once
#include "common.hpp"
#include "logging.hpp"

#include "Tester.hpp"
#include "TestResults.hpp"

namespace TesterLib {
    /**
     * @brief Class for unit tests.
     */
    class Test : public Tester {
        private:
            /**
             * @brief The name of the component.
             */
            std::string component_name;

            /**
             * @brief The name of the module.
             */
            std::string module_name;

            /**
             * @brief The name of the test.
             */
            std::string name;
        protected:
            /**
             * @brief Run this test.
             * @return The results of the test.
             */
            virtual TestResults run() const = 0;
        public:
            /**
             * @brief Constructor.
             * @param component_name The name of the component.
             * @param module_name The name of the module.
             * @param name The name of the test.
             */
            Test(std::string component_name, std::string module_name,
                 std::string name) : component_name(std::move(component_name)), module_name(std::move(module_name)),
                                     name(std::move(name)) {}

            /**
             * @brief Gets the name of the test.
             * @return The name.
             */
            std::string get_name() const override;

            /**
             * @brief Gets the full name of the test.
             * @return The full name.
             */
            std::string get_full_name() const override;

            /**
             * @brief Run the test.
             * @return The results of the test.
             */
            Results test() const override;
    };

} // TesterLib
