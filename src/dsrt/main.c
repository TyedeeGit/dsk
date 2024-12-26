/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file main.c
 * @author Gianmarco Lenzi
 * @brief Main source file.
 */

#include "main.h"

void dsrt_init(void) {
    dsrt_simple_heap_init();
    dsrt_term_heap_init();
}

void dsrt_deinit(void) {
    dsrt_simple_heap_deinit();
    dsrt_term_heap_deinit();
}
