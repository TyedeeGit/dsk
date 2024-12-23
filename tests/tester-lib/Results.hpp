/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file Results.hpp
 * @author Gianmarco Lenzi
 * @brief Header for results class.
 */

#pragma once
#include "common.hpp"

namespace TesterLib {
    /**
     * @brief Class for storing test results.
     */
    class Results {
        private:
            /**
             * @brief The total amount of tests.
             */
            const unsigned total;

            /**
             * @brief The amount of passed tests.
             */
            const unsigned passed;
        protected:
            /**
             * @brief The warnings messages generated.
             */
            std::unordered_map<std::string, std::string> warnings;

            /**
             * @brief Gets the amount of passed tests.
             * @return The amount of passed tests.
             */
            unsigned get_passed() const { return passed; }

            /**
             * @brief Constructor initializing the total and passed, no warnings.
             * @param total The total amount of tests.
             * @param passed The amount of passed tests.
             */
            Results(const unsigned total, const unsigned passed) : total(total), passed(passed) {}
        public:
            /**
             * @brief Constructor
             * @param total The total amount of tests.
             * @param passed The amount of passed tests.
             * @param warnings The warnings messages generated.
             */
            Results(const unsigned total, const unsigned passed,
                    std::unordered_map<std::string, std::string> &warnings) : total(total), passed(passed),
                warnings(std::move(warnings)) {}

            /**
             * @brief Gets the total amount of tests.
             * @return The total amount of tests.
             */
            unsigned get_total() const { return total; }

            /**
             * @brief Whether the test results are a pass.
             * @return True if the test results are a pass, false otherwise.
             */
            bool is_pass() const { return passed == total; }

            /**
             * @brief Get the total warnings generated.
             * @return The total warnings.
             */
            unsigned get_total_warnings() const { return warnings.size(); }
    };

} // TesterLib
