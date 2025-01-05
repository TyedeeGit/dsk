/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file common.hpp
 * @author Gianmarco Lenzi
 * @brief Common header for testers.
 */

#pragma once
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <optional>

/**
 * @brief Namespace for logging.
 */
namespace Logging {}

/**
 * @brief Namespace for testers.
 */
namespace TesterLib {
    class TestLogger;

    /**
     * @brief A dictionary.
     * @details Alias for @code std::map@endcode.
     */
    template <typename T, typename U>
    using Dict = std::map<T, U>;

    /**
     * @brief A pair.
     * @details Alias for @code std::pair@endcode.
     */
    template <typename T, typename U>
    using Pair = std::pair<T, U>;

    /**
     * @brief An optional.
     * @details Alias for @code std::optional@endcode.
     */
    template <typename T>
    using Optional = std::optional<T>;

    /**
     * @brief A list of items.
     * @details Alias for @code std::vector@endcode.
     */
    template <typename T>
    using List = std::vector<T>;

    /**
     * @brief A string.
     * @details Alias for @code std::string@endcode.
     */
    using String = std::string;

    /**
     * @brief A name for a component.
     * @details Alias for @code String@endcode.
     */
    using ComponentName = String;

    /**
     * @brief A name for a module.
     * @details Alias for @code String@endcode.
     */
    using ModuleName = String;

    /**
     * @brief A name for a test within a module.
     * @details Alias for @code String@endcode.
     */
    using TestName = String;

    /**
     * @brief A message that can be logged.
     * @details Alias for @code String@endcode.
     */
    using Message = String;

    /**
     * @brief A list of test names for a module.
     * @details Alias for @code List<TestName>@endcode.
     */
    using ModuleTestNames = List<TestName>;

    /**
     * @brief A map of module names to their tests.
     * @details Alias for @code Dict<ModuleName, ModuleTests>@endcode.
     */
    using TestNameList = Dict<ModuleName, ModuleTestNames>;

    /**
     * @brief A fully-qualified name for a test.
     * @details Alias for @code Pair<ModuleName, TestName>@endcode.
     */
    using QualifiedName = Pair<ModuleName, TestName>;

    /**
     * @brief A test.
     * @details Alias for @code void(*)(const TestLogger &logger)@endcode.
     */
    using Test = void(*)(const TestLogger &logger);

    /**
     * @brief A map of test names to tests.
     * @details Alias for @code Dict<TestName, Test>@endcode.
     */
    using ModuleTests = Dict<TestName, Test>;

    /**
     * @brief A map of module names to their tests.
     * @details Alias for @code Dict<ModuleName, ModuleTests>@endcode.
     */
    using TestList = Dict<ModuleName, ModuleTests>;

    /**
     * @brief A map of fully-qualified test names to their failure messages.
     * @details Alias for @code Dict<QualifiedName, Optional<Message>>@endcode.
     */
    using FailureMessages = Dict<QualifiedName, Optional<Message>>;

    /**
     * @brief A map of fully-qualified test names to their warning messages.
     * @details Alias for @code Dict<QualifiedName, List<Message>>@endcode.
     */
    using WarningMessages = Dict<QualifiedName, List<Message>>;
} // TesterLib
