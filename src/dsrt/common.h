/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file common.h
 * @author Gianmarco Lenzi
 * @brief Common header file for the DSRT library.
 */

#pragma once

#ifdef __cplusplus
#include <cstdbool>
#include <cstdlib>
#include <cstdio>
#else
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief DSRT object type.
 * @details A DSRT object is anything.
 */
typedef void *DSRTAny;

/**
 * @brief DSRT term type.
 * @details A term is a DSRT object, and can have an arbitrary memory layout.
 */
typedef DSRTAny DSRTTerm;

/**
 * @brief DSRT size type.
 * @details Implemented as a size_t.
 */
typedef size_t DSRTSize;

/**
 * @brief DSRT index type.
 * @details Implemented as a size_t.
 */
typedef size_t DSRTIndex;

/**
 * @brief DSRT size arguments type.
 */
typedef struct {
    /**
     * @brief Number of arguments.
     */
    DSRTSize  argc;

    /**
     * @brief Arguments.
     */
    DSRTSize *argv;
} DSRTSizeArgs;

/**
 * @brief DSRT size arguments array type.
 */
typedef struct {
    /**
     * @brief Number of arguments in the array.
     */
    DSRTSize      argsc;

    /**
     * @brief Arguments array.
     */
    DSRTSizeArgs *argsv;
} DSRTSizeArgsArray;

/**
 * @brief Free all DSRT objects.
 */
void dsrt_free_all(void);

/**
 * @brief Initialize DSRT library.
 */
void dsrt_init(void);

/**
 * @brief Deinitialize DSRT library.
 */
void dsrt_deinit(void);

/**
 * @brief Create a singleton size args.
 * @details Creates a singleton DSRTSizeArgs object.
 * @param size The argument of the singleton.
 * @returns A singleton DSRTSizeArgs object.
 */
DSRTSizeArgs dsrt_size_args_singleton(DSRTSize size);

/**
 * @brief Create an empty size args.
 * @details Creates an empty DSRTSizeArgs object.
 * @returns An empty DSRTSizeArgs object.
 */
DSRTSizeArgs dsrt_size_args_empty(void);

#ifdef __cplusplus
}
#endif