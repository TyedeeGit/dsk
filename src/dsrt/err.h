/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file err.h
 * @author Gianmarco Lenzi
 * @brief Header for DSRT error handling.
 */

#pragma once
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Types of errors that can be raised by the DSRT.
 * @see DSRTErrorInfo
 */
typedef enum {
    /**
     * @brief Memory error.
     * @details A memory error is raised when the DSRT cannot allocate memory.
     */
    DSRT_MEMORY_ERROR = 0,

    /**
     * @brief Unsound error.
     * @details An unsound error is raised when the DSRT has encountered an
     * invalid program.
     */
    DSRT_UNSOUND_ERROR = 1,

    /**
     * @brief ABI error.
     * @details An ABI error is raised when invalid ABI calls are made.
     */
    DSRT_ABI_ERROR    = 2
} DSRTErrorType;

/**
 * @brief DSRT error information.
 */
typedef struct {
    /**
     * @brief The type of the error.
     * @see DSRTErrorType
     */
    const DSRTErrorType type;

    /**
     * @brief A human-readable description of the error.
     */
    const char *message;
} DSRTErrorInfo;

static const DSRTErrorInfo DSRT_OUT_OF_MEMORY = {DSRT_MEMORY_ERROR, "Out of memory!"};
static const DSRTErrorInfo DSRT_BAD_SIZE_ARG = {DSRT_MEMORY_ERROR, "Invalid size argument!"};
static const DSRTErrorInfo DSRT_INVALID_HEAP = {DSRT_MEMORY_ERROR, "Invalid heap!"};
static const DSRTErrorInfo DSRT_NULL_POINTER = {DSRT_MEMORY_ERROR, "Null pointer passed as argument!"};

static const DSRTErrorInfo DSRT_BAD_CTYPE = {DSRT_ABI_ERROR, "Invalid ctype descriptor!"};
static const DSRTErrorInfo DSRT_FAILED_UNPACK = {DSRT_UNSOUND_ERROR, "Failed to unpack object!"};

#ifndef __cplusplus
/**
 * @brief Flag indicating whether the DSRT runtime can be deinitialized.
 */
bool can_deinit;

/**
 * @brief Prevents further deinitialization of the DSRT runtime.
 * @details This function sets an internal flag indicating that deinitialization
 * should no longer be possible, typically used to ensure the runtime
 * remains active until program termination.
 */
inline void dsrt_start_deinit(void) { can_deinit = false; }

/**
 * @brief Queries whether the DSRT runtime can be deinitialized.
 * @details This function returns a boolean indicating whether the DSRT runtime
 * can be deinitialized. If the function returns `false`, then the runtime
 * cannot be deinitialized until program termination.
 * @return `true` if the runtime can be deinitialized, `false` otherwise.
 */
inline bool dsrt_can_deinit(void) { return can_deinit; }

#endif

/**
 * @brief Exit the DTL runtime.
 * @param code The exit code.
 */
void dsrt_exit(int code);

/**
 * @brief Raise a runtime error.
 * @param info The error information.
 */
void dsrt_error(DSRTErrorInfo info);

#ifdef __cplusplus
}
#endif