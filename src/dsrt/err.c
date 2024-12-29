/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file err.c
 * @author Gianmarco Lenzi
 * @brief Implementation of DSRT error handling.
 */

#include "common.h"
#include "err.h"
#include <stdlib.h>
#include <stdio.h>

void dsrt_exit(const int code) {
    // Deinitialize the DTL runtime.
    dsrt_deinit();

    // Exit with the given code.
    exit(code);
}

void dsrt_error(const DSRTErrorInfo info) {
    // Print the error message.
    fprintf(stderr, "DTL runtime error: %s\n", info.message);

    if (dsrt_can_deinit()) {
        // Exit safely if deinitialization was possible.
        dsrt_exit(1);
    } else {
        // Report if deinitialization was not possible.
        fprintf(stderr, "The above error occurred while attempting to deinitialize the DTL runtime, "
                        "so the program will exit without cleanup.\n");

        // Exit without deinitializing.
        exit(1);
    }
}
