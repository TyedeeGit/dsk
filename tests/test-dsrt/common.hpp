/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file common.hpp
 * @author Gianmarco Lenzi
 * @brief Common header for the DSRT tester.
 */

#pragma once
#include "../tester-lib/all.hpp"
#include "../../src/dsrt/main.h"

/**
 * @brief Namespace for the DSRT tester.
 */
namespace TestDSRT {
    using namespace Logging;
    using namespace TesterLib;

    const std::string component_name = "dsrt";
} // TestDSRT