/*
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file tests/Logging/logging.cpp
 * @author Gianmarco Lenzi
 * @brief Test logging helpers.
 */

#include "logging.hpp"

namespace Logging {
    void log_begin() {
        std::cout << "[INFO] ALL: Begin testing." << std::endl;
    }

    void log_module_begin(const std::string& module_name) {
        std::cout << "[INFO] " << module_name << ": Begin testing." << std::endl;
    }

    void log_test_begin(const std::string& module_name, const std::string& test_name) {
        std::cout << "[INFO] " << module_name << "." << test_name << ": Begin testing." << std::endl;
    }

    void log_test_pass(const std::string& module_name, const std::string& test_name){
        passed++;
        std::cout << "[PASS] " << module_name << "." << test_name << ": Test passed!" << std::endl;
    }

    void log_test_warn(const std::string& module_name, const std::string& test_name, const std::string& message) {
        warnings++;
        std::cout << "[WARN] " << module_name << "." << test_name << ": " << message << std::endl;
    }

    void log_test_fail(const std::string& module_name, const std::string& test_name, const std::string& message) {
        failed = true;
        std::cout << "[FAIL] " << module_name << "." << test_name << ": " << message << std::endl;
        log_module_fail(module_name);
    }

    void log_module_pass(const std::string& module_name) {
        std::cout << "[PASS] " << module_name << ": All tests passed!"<< std::endl;
    }

    void log_module_fail(const std::string& module_name) {
        std::cout << "[FAIL] " << module_name << ": Some test failed."<< std::endl;
    }

    void log_results() {
        if (failed) {
            if (warnings > 0) {
                std::cout << "[FAIL] ALL: Testing failed after " << passed << " tests with " << warnings << " warnings. :(" << std::endl;
            } else {
                std::cout << "[FAIL] ALL: Testing failed after " << passed << " tests with no warnings. :(" << std::endl;
            }
        } else {
            if (warnings > 0) {
                std::cout << "[PASS] ALL: " << passed << " tests passed with " << warnings << " warnings! :)" << std::endl;
            } else {
                std::cout << "[PASS] ALL: " << passed << " tests passed with no warnings! :D" << std::endl;
            }
        }
    }
}