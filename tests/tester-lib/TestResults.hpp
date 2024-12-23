/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file TestResults.hpp
 * @author Gianmarco Lenzi
 * @brief Header for test results class.
 */

#pragma once
#include "common.hpp"
#include "Results.hpp"

namespace TesterLib {

    /**
    * @brief Class for storing test results.
    */
    class TestResults : public Results {
        public:
            /**
             * @brief No argument constructor.
             */
            TestResults() : Results(1, true) {}

            /**
             * @brief Constructor.
             * @param passed The amount of passed tests.
             * @param warnings The warnings messages generated.
             */
            TestResults(bool passed, const std::unordered_set<std::string>& warnings);

            /**
             * @brief Get the warnings messages generated.
             * @return The warnings.
             */
            std::unordered_set<std::string> get_warnings() const;
    };

} // TesterLib
