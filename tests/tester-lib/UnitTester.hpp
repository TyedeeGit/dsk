/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file UnitTester.hpp
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
    class UnitTester : public Tester {
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

            /**
             * @brief Gets the name of the test.
             * @return The name of the test.
             */
            virtual std::string get_test_name() const = 0;

            /**
             * @brief Gets the name of the module that the test belongs to.
             * @return The name of the module.
             */
            virtual std::string get_module_name() const = 0;

            /**
             * @brief Gets the name of the component that the test belongs to.
             * @return The name of the component.
             */
            virtual std::string get_component_name() const = 0;
        public:
            /**
             * @brief Constructor.
             */
            UnitTester() = default;

            /**
             * @brief Gets the fully qualified name of the test.
             * @return The full name in the format "component_name.module_name.test_name".
             */
            std::string get_full_name() const override {
                return this->get_component_name() + "." + this->get_module_name() + "." + this->get_test_name();
            }

            /**
             * @brief Gets the name of the test.
             * @return The name of the test.
             */
            std::string get_name() const override {
                return this->get_test_name();
            }

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
