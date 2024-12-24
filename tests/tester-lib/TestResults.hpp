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
        private:
            /**
             * @brief The warnings messages generated.
             */
            TestWarnings warnings;
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
            TestResults(bool passed, const TestWarnings& warnings);


            /**
             * @brief Get the total amount of warnings.
             * @return The total amount of warnings.
             */
            unsigned get_total_warnings() const override;

            /**
             * @brief Get the warnings messages generated.
             * @return The warnings.
             */
            TestWarnings get_warnings() const;

            /**
             * @brief Add a warning message.
             * @param warning The warning message to add.
             */
            void add_warning(const std::string& warning);

            /**
             * @brief Fail the test.
             */
            void fail();
    };

} // TesterLib
