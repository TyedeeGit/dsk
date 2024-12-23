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

namespace Testers {
    /**
     * @brief Class for storing test results.
     */
    class Results {
        private:
            /**
             * @brief The full name of the test where the results are sourced.
             */
            const std::string full_name;

            /**
             * @brief The name of the test where the results are sourced.
             */
            const std::string name;

            /**
             * @brief The total amount of tests.
             */
            const unsigned total;

            /**
             * @brief The amount of passed tests.
             */
            const unsigned passed;

            /**
             * @brief The warnings messages generated.
             */
            const std::unordered_map<std::string, std::string> warnings;
        protected:
            /**
             * @brief Gets the amount of passed tests.
             * @return The amount of passed tests.
             */
            unsigned get_passed() const { return passed; }

            /**
             * @brief Gets the warnings messages generated.
             * @return The warnings.
             */
            std::unordered_map<std::string, std::string> get_warnings() const { return warnings; }
        public:
            /**
             * @brief Constructor
             * @param full_name The full name of the test where the results are sourced.
             * @param name The name of the test where the results are sourced.
             * @param total The total amount of tests.
             * @param passed The amount of passed tests.
             * @param warnings The warnings messages generated.
             */
            Results(std::string full_name, std::string name, const unsigned total, const unsigned passed, const std::unordered_map<std::string, std::string> &warnings)
                : full_name(std::move(full_name)), name(std::move(name)), total(total), passed(passed), warnings(warnings) {}

            /**
             * @brief Gets the full name of the test where the results are sourced.
             * @return The full name.
             */
            std::string get_full_name() const { return full_name; }

            /**
             * @brief Gets the name of the test where the results are sourced.
             * @return The name.
             */
            std::string get_name() const { return name; }

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

} // Testers
