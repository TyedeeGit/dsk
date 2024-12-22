/*
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file tests/Logging/logging.hpp
 * @author Gianmarco Lenzi
 * @brief Header for test logging helpers.
 */

#pragma once
#include "common.hpp"

namespace Logging{
    /*
     * @brief The number of tests passed.
     */
    static unsigned passed = 0;

    /*
     * @brief The number of warnings raised.
     */
    static unsigned warnings = 0;

    /*
     * @brief Whether any tests failed.
     */
    static bool failed = false;

    /*
     * @brief Begin testing.
     */
    void log_begin();

    /*
     * @brief Begin test module.
     * @param module_name The name of the module.
     */
    void log_module_begin(const std::string& module_name);

    /*
     * @brief Begin test.
     * @param module_name The name of the module.
     * @param test_name The name of the test.
     */
    void log_test_begin(const std::string& module_name, const std::string& test_name);

    /*
     * @brief Logs a test pass.
     * @param module_name The name of the module.
     * @param test_name The name of the test.
     * @param message The message to log.
     */
    void log_test_pass(const std::string& module_name, const std::string& test_name);

    /*
     * @brief Logs a test warning.
     * @param module_name The name of the module.
     * @param test_name The name of the test.
     * @param message The message to log.
     */
    void log_test_warn(const std::string& module_name, const std::string& test_name, const std::string& message);

    /*
     * @brief Logs a test failure.
     * @param module_name The name of the module.
     * @param test_name The name of the test.
     * @param message The message to log.
     */
    void log_test_fail(const std::string& module_name, const std::string& test_name, const std::string& message);

    /*
     * @brief Logs a module pass.
     * @param module_name The name of the module.
     */
    void log_module_pass(const std::string& module_name);

    /*
     * @brief Logs a module failure.
     * @param module_name The name of the module.
     */
    void log_module_fail(const std::string& module_name);

    /*
     * @brief Logs all test results.
     */
    void log_results();
}
