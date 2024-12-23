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
        // Convert the warnings set to a map(keys are empty strings)
        std::unordered_map<std::string, std::string> warnings_map;
        for (const auto &warning: warnings) {
            warnings_map[""] = warning;
        }

        // Set the warnings
        this->warnings = warnings_map;
    }


    std::unordered_set<std::string> TestResults::get_warnings() const {
        // Get the warnings as a map
        std::unordered_map<std::string, std::string> warnings_map = this->warnings;
        std::unordered_set<std::string> warnings;

        // Convert the map to a set
        for (auto &[fst, snd] : warnings_map) {
            warnings.insert(snd);
        }

        // Return the set
        return warnings;
    }
} // TesterLib