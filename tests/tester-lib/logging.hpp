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
     * @brief The ANSI escape code prefix.
     */
    const std::string ANSI = "\033[";

    /**
     * @brief The color code for reset.
     */
    const std::string RESET = ANSI + "0m";

    /**
     * @brief The color code for green.
     */
    const std::string GREEN = ANSI + "32m";

    /**
     * @brief The color code for yellow.
     */
    const std::string YELLOW = ANSI + "33m";

    /**
     * @brief The color code for red.
     */
    const std::string RED = ANSI + "31m";

    /**
     * @brief The type of message to log.
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
     * @brief Converts a MessageType to a color string.
     * @param type The type of message to convert.
     * @return A color string in the format "\003[<color_code>m" that can be used to color the output,
     *         or an empty string if the type is not recognized.
     */
    std::string to_color(MessageType type);

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
    inline void log_info(const std::string& scope, const std::string& message) { log(MessageType::INFO, scope, message); }

    /**
     * @brief Log a pass message.
     * @param scope The scope of the message.
     * @param message The message to log.
     */
    inline void log_pass(const std::string& scope, const std::string& message) { log(MessageType::PASS, scope, message); }

    /**
     * @brief Log a warn message.
     * @param scope The scope of the message.
     * @param message The message to log.
     */
    inline void log_warn(const std::string& scope, const std::string& message) { log(MessageType::WARN, scope, message); }

    /**
     * @brief Log a fail message.
     * @param scope The scope of the message.
     * @param message The message to log.
     */
    inline void log_fail(const std::string& scope, const std::string& message) { log(MessageType::FAIL, scope, message); }
}
