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
        protected:
            /**
             * @brief Run this test.
             * @return The results of the test.
             */
            virtual TestResults run() const = 0;
        public:
            /**
             * @brief Constructor.
             */
            Test() = default;

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
