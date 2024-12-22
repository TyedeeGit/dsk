/*
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file src/common.h
 * @author Gianmarco Lenzi
 * @brief Common header file for the DSRT library.
 */

#pragma once

#ifdef __cplusplus
#include <cstddef>
#include <cstdlib>
#else
#include <stddef.h>
#include <stdlib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief DSRT object type.
 * @details A DSRT object is anything.
 */
typedef void *DSRTAny;

/*
 * @brief DSRT term type.
 * @details A term is a DSRT object, and can have an arbitrary memory layout.
 */
typedef DSRTAny DSRTTerm;

/*
 * @brief DSRT size type.
 * @details Implemented as a size_t.
 */
typedef size_t DSRTSize;

/*
 * @brief DSRT index type.
 * @details Implemented as a size_t.
 */
typedef size_t DSRTIndex;

/*
 * @brief DSRT size arguments type.
 */
typedef struct {
    DSRTSize  argc;
    DSRTSize *argv;
} DSRTSizeArgs;

typedef struct {
    DSRTSize      argsc;
    DSRTSizeArgs *argsv;
} DSRTSizeArgsArray;

/*
 * @brief Free all DSRT objects.
 */
void dsrt_free_all(void);

/*
 * @brief Initialize DSRT library.
 */
void dsrt_init(void);

/*
 * @brief Uninitialize DSRT library.
 */
void dsrt_exit(void);

/*
 * @brief Create a singleton size args.
 * @details Creates a singleton DSRTSizeArgs object.
 * @returns A singleton DSRTSizeArgs object.
 */
DSRTSizeArgs dsrt_size_args_singleton(DSRTSize size);

/*
 * @brief Create an empty size args.
 * @details Creates an empty DSRTSizeArgs object.
 * @returns An empty DSRTSizeArgs object.
 */
DSRTSizeArgs dsrt_size_args_empty(void);

#ifdef __cplusplus
}
#endif