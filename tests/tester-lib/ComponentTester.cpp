/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file ComponentTester.cpp
 * @author Gianmarco Lenzi
 * @brief Implementation of the component tester class.
 */

#include "ComponentTester.hpp"

namespace TesterLib {
    ComponentResults ComponentTester::test_all() const {
        // Log the start of the tests.
        Logging::log_info(this->get_full_name(), "Running tests...");

        // Initialize the results.
        ComponentResults results;

        // Run all the modules.
        for (const auto &module : this->get_modules()) {
            results.add_module(module.get_full_name(), module.test_all());
        }

        // TODO: Log the results

        // Return the results.
        return results;
    }

} // TesterLib