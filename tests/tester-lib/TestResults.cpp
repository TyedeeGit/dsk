/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file TestResults.cpp
 * @author Gianmarco Lenzi
 * @brief Test results class implementation.
 */

#include "TestResults.hpp"

namespace TesterLib {
    TestResults::TestResults(const bool passed, const TestWarnings &warnings): Results(1, passed) {
        this->warnings = warnings;
    }

    unsigned TestResults::get_total_warnings() const {
        return this->warnings.size();
    }

    TestWarnings TestResults::get_warnings() const {
        return this->warnings;
    }

    void TestResults::add_warning(const std::string &warning) {
        this->warnings.insert(warning);
    }

    void TestResults::fail() {
        this->set_passed(0);
    }
} // TesterLib