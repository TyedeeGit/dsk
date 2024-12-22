/*
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file tests/main.hpp
 * @author Gianmarco Lenzi
 * @brief Main header for the tests.
 */

#pragma once
#include "common.hpp"
#include "Logging/logging.hpp"
#include "TestDSRT/all.hpp"

/*
 * @brief Runs all the tests.
 * @return True if all the tests passed, false otherwise.
 */
bool test_all();

/*
 * @brief Entry point for the tests.
 * @return 0 if all the tests passed, 1 otherwise.
 */
int main();