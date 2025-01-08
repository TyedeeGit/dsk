/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file main.c
 * @author Gianmarco Lenzi
 * @brief Main source file.
 */

#include "dsrt_memory.h"
#include "err.h"
#include <stdbool.h>


void dsrt_init(void) {
    can_deinit = true;
}

void dsrt_deinit(void) {
    dsrt_start_deinit();
}
