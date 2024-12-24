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
             * @brief The results of the test.
             */
            mutable TestResults results;
        protected:
            /**
             * @brief Adds a warning message to the test results.
             * @param message The warning message to add.
             */
            void warn(const std::string& message) const {
                Logging::log_warn(this->get_full_name(), message);
                this->results.add_warning(message);
            }

            /**
             * @brief Fail the test with the given message.
             * @param message The message to log for the failure.
             */
            void fail(const std::string &message) const {
                Logging::log_fail(this->get_full_name(), message);
                this->results.fail(message);
            }

            /**
             * @brief Run the test.
             */
            virtual void run() const = 0;
        public:
            /**
             * @brief Constructor.
             */
            Test() = default;

            /**
             * @brief Run the test.
             * @return The results of the test.
             */
            virtual TestResults test() const {
                Logging::log_info(this->get_full_name(), "Running test...");
                this->run();
                if (this->results.get_passed()) {
                    if (this->results.get_warnings_count() > 0) {
                        Logging::log_warn(this->get_full_name(),
                            "Test passed with "
                            + std::to_string(this->results.get_warnings_count())
                            + " warning(s).");
                    } else {
                        Logging::log_pass(this->get_full_name(), "Test passed with no warnings.");
                    }
                }
                return this->results;
            }
    };

} // TesterLib
