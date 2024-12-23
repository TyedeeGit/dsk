/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file Test.cpp
 * @author Gianmarco Lenzi
 * @brief Implementation for unit test class.
 */

#include "Test.hpp"

namespace TesterLib {
    Results Test::test() const {
        // Log the start of the test
        Logging::log_info(get_full_name(), "Running test...");
        // Run the test
        return run();
    }

} // TesterLib