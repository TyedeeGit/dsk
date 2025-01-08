/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file dsrt_memory.h
 * @author Gianmarco Lenzi
 * @brief Memory management header for the DSRT library.
 */

#pragma once
#include "common.h"
#include "abi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DSRT_OBJ_GENERAL = 0,
    DSRT_OBJ_CTYPE = 1,
    DSRT_OBJ_BOOL = 2,
    DSRT_OBJ_ARRAY = 3,
    DSRT_OBJ_LIST = 4,
    DSRT_OBJ_STRUCT = 5,
    DSRT_OBJ_UNION = 6,
    DSRT_OBJ_SUM = 7
} DSRTObjectKind;

#ifdef __cplusplus
}
#endif
