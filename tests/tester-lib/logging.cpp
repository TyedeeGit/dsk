/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file logging.cpp
 * @author Gianmarco Lenzi
 * @brief Test logging helpers.
 */

#include "logging.hpp"
#include <termcolor/termcolor.hpp>

namespace Logging {
    std::string to_string(const MessageType type) {
        switch (type) {
            case MessageType::INFO:
                return "INFO";
            case MessageType::PASS:
                return "PASS";
            case MessageType::WARN:
                return "WARN";
            case MessageType::FAIL:
                return "FAIL";
            default:
                return "";
        }
    }


    void log(const MessageType type, const std::string& scope, const std::string& message) {
        switch (type) {
            case MessageType::INFO:
                std::cout << "[INFO] " << scope << ": " << message << std::endl;
                return;
            case MessageType::PASS:
                std::cout << termcolor::bright_green << "[PASS] " << scope << ": " << message << termcolor::reset << std::endl;
                return;
            case MessageType::WARN:
                std::cout << termcolor::bright_yellow << "[WARN] " << scope << ": " << message << termcolor::reset << std::endl;
                return;
            case MessageType::FAIL:
                std::cout << termcolor::red << "[FAIL] " << scope << ": " << message << termcolor::reset << std::endl;
                return;
        }
    }
}