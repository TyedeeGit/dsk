/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file TestResults.cpp
 * @author Gianmarco Lenzi
 * @brief Test results class implementation.
 */

#include "TestResults.hpp"

namespace TesterLib {
    TestResults::TestResults(const unsigned total, const bool passed,
                             const std::unordered_set<std::string> &warnings): Results(total, passed) {
        std::unordered_map<std::string, std::string> warnings_map;

        // Convert the warnings set to a map(keys are empty strings)
        for (const auto &warning: warnings) {
            warnings_map[""] = warning;
        }

        // Set the warnings
        this->warnings = std::move(warnings_map);
    }


    std::unordered_set<std::string> TestResults::get_warnings() const {
        std::unordered_set<std::string> warnings;

        // Convert the map to a set
        // ReSharper disable once CppUseStructuredBinding
        for (const auto& pair : this->warnings) {
            warnings.insert(pair.second);
        }

        // Return the set
        return warnings;
    }
} // TesterLib