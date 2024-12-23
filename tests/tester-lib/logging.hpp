/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file logging.hpp
 * @author Gianmarco Lenzi
 * @brief Header for test logging helpers.
 */

#pragma once
#include "common.hpp"

namespace Logging{
    /**
     * @brief The type of message to log(INFO, PASS, WARN, FAIL).
     */
    enum class MessageType {
        /** @brief Informational message. */
        INFO,

        /** @brief Pass message. */
        PASS,

        /** @brief Warning message. */
        WARN,

        /** @brief Fail message. */
        FAIL
    };

    /**
     * @brief Converts a MessageType to a string.
     * @param type The type of message to convert.
     * @return The string representation of the message type.
     */
    std::string to_string(MessageType type);

    /**
     * @brief Logs a message.
     * @param type The type of message to log.
     * @param scope The scope of the message.
     * @param message The message to log.
     */
    void log(MessageType type, const std::string& scope, const std::string& message);

    /**
     * @brief Log an info message.
     * @param scope The scope of the message.
     * @param message The message to log.
     */
    void log_info(const std::string& scope, const std::string& message) { log(MessageType::INFO, scope, message); }

    /**
     * @brief Log a pass message.
     * @param scope The scope of the message.
     * @param message The message to log.
     */
    void log_pass(const std::string& scope, const std::string& message) { log(MessageType::PASS, scope, message); }

    /**
     * @brief Log a warn message.
     * @param scope The scope of the message.
     * @param message The message to log.
     */
    void log_warn(const std::string& scope, const std::string& message) { log(MessageType::WARN, scope, message); }

    /**
     * @brief Log a fail message.
     * @param scope The scope of the message.
     * @param message The message to log.
     */
    void log_fail(const std::string& scope, const std::string& message) { log(MessageType::FAIL, scope, message); }
}
