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
            unsigned total;

            /**
             * @brief The amount of passed tests.
             */
            unsigned passed;
        protected:
            /**
             * @brief Gets the amount of passed tests.
             * @return The amount of passed tests.
             */
            unsigned get_passed() const { return passed; }

            /**
             * @brief Sets the amount of passed tests.
             * @param passed The new amount of passed tests.
             */
            void set_passed(const unsigned passed) { this->passed = passed; }

            /**
             * @brief Constructor initializing the total and passed, no warnings.
             * @param total The total amount of tests.
             * @param passed The amount of passed tests.
             */
            Results(const unsigned total, const unsigned passed) : total(total), passed(passed) {}
        public:
            /**
             * @brief No argument constructor.
             */
            Results() : total(0), passed(0) {}

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
             * @brief Gets the total amount of warnings.
             * @return The total amount of warnings.
             */
            virtual unsigned get_total_warnings() const = 0;
    };

} // TesterLib
