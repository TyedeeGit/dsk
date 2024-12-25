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

    std::string to_color(const MessageType type) {
        switch (type) {
            case MessageType::INFO:
                return RESET;
            case MessageType::PASS:
                return GREEN;
            case MessageType::WARN:
                return YELLOW;
            case MessageType::FAIL:
                return RED;
            default:
                return "";
        }
    }


    void log(const MessageType type, const std::string& scope, const std::string& message) {
        std::cout << to_color(type) << "[" << to_string(type) << "] " << scope << ": " << message << RESET << std::endl;
    }
}