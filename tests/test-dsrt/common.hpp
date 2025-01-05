/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file common.hpp
 * @author Gianmarco Lenzi
 * @brief Common header for the DSRT tester.
 */

#pragma once
#include "../tester-lib/all.hpp"

/**
 * @brief Namespace for the DSRT tester.
 */
namespace TestDSRT {
    using namespace Logging;
    using namespace TesterLib;

    const std::string component_name = "dsrt";
} // TestDSRT