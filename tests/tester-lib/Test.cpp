/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file Test.cpp
 * @author Gianmarco Lenzi
 * @brief Implementation for unit test class.
 */

#include "Test.hpp"

namespace TesterLib {
    std::string Test::get_name() const {
        return name;
    }

    std::string Test::get_full_name() const {
        return module_name + "." + component_name + "." + name;
    }

    Results Test::test() const {
        Logging::log_info(get_full_name(), "Running test...");
        return run();
    }

} // TesterLib