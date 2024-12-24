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
        public:
            /**
             * @brief Constructor.
             */
            Test() = default;

            /**
             * @brief Run the test.
             * @return The results of the test.
             */
            virtual TestResults test() const = 0;
    };

} // TesterLib
