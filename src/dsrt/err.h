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

typedef enum {
    DSRT_MEMORY_ERROR = 0,
    DSRT_UNSOUND_ERROR = 1
} DSRTErrorType;

/**
 * @brief DSRT error information.
 */
typedef struct {
    /**
     * @brief False if the error occurred while deinitializing.
     */
    const bool can_deinit;

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