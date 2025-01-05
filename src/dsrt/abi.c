/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file abi.c
 * @author Gianmarco Lenzi
 * @brief Implementation of the DSRT ABI helper functions.
 */

#include "abi.h"
#include "err.h"
#include <string.h>

DSRTBuffer dsrt_alloc_buffer(const DSRTSize size) {
    // Allocate the buffer.
    const DSRTBuffer buffer = {size, malloc(size)};

    // Check if the allocation was successful.
    if (buffer.data == NULL) {
        dsrt_error(DSRT_OUT_OF_MEMORY);
        return (DSRTBuffer) {};
    }

    // Return the buffer.
    return buffer;
}

void dsrt_realloc_buffer(DSRTBuffer *buffer, const DSRTSize size) {
    // Reallocate the buffer.
    void *new_data = realloc(buffer->data, size);

    // Check if the reallocation was successful.
    if (new_data == NULL) {
        dsrt_error(DSRT_OUT_OF_MEMORY);
        return;
    }

    // Update the buffer.
    buffer->size = size;
    buffer->data = new_data;
}

void dsrt_free_buffer(const DSRTBuffer buffer) {
    // Free the buffer.
    free(buffer.data);
}

void dsrt_copy_buffer(const DSRTBuffer dest, const DSRTBuffer src, const DSRTSize dest_offset, const DSRTSize src_offset) {
    // Check if the buffers are valid.
    if (dest.data == NULL || src.data == NULL) {
        dsrt_error(DSRT_NULL_POINTER);
        return;
    }

    // Check if the destination buffer is large enough to hold the data.
    if (dest.size - dest_offset < src.size - src_offset) {
        dsrt_error(DSRT_BAD_SIZE_ARG);
        return;
    }

    // Copy the data.
    memcpy(dest.data + dest_offset, src.data + src_offset, src.size - src_offset);
}

DSRTSeeker dsrt_seeker_new(const DSRTBuffer buffer) {
    // Create the seeker.
    return (DSRTSeeker) {buffer, 0};
}

DSRTBuffer dsrt_seeker_read(DSRTSeeker *seeker, const DSRTSize size) {
    // Check if the size is valid.
    if (size >= seeker->buffer.size - seeker->position) {
        dsrt_error(DSRT_BAD_SIZE_ARG);
    }

    // Allocate the buffer.
    const DSRTBuffer buffer = dsrt_alloc_buffer(size);

    // Copy the data.
    dsrt_copy_buffer(buffer, seeker->buffer, 0, seeker->position);

    // Update the position.
    seeker->position += size;

    // Return the buffer.
    return buffer;
}

void dsrt_seeker_write(DSRTSeeker *seeker, const DSRTBuffer buffer) {
    // Check if the size is valid.
    if (buffer.size > seeker->buffer.size - seeker->position) {
        dsrt_error(DSRT_BAD_SIZE_ARG);
    }

    // Copy the data.
    dsrt_copy_buffer(seeker->buffer, buffer, seeker->position, 0);

    // Update the position.
    seeker->position += buffer.size;
}

void dsrt_seeker_resize(DSRTSeeker *seeker, const DSRTSize size) {
    // Reallocate the buffer.
    dsrt_realloc_buffer(&seeker->buffer, size);
}

void dsrt_seeker_goto(DSRTSeeker *seeker, const DSRTSize position) {
    // Check if the position is valid.
    if (position > seeker->buffer.size) {
        dsrt_error(DSRT_BAD_SIZE_ARG);
    }

    // Update the position.
    seeker->position = position;
}

DSRTInt8 dsrt_unpack_int8(DSRTSeeker *seeker) {
    // Read the value directly from the buffer.
    const DSRTInt8 value = dsrt_ensure_int8(*(DSRTInt8 *) (seeker->buffer.data + seeker->position));

    // Update the position.
    seeker->position += sizeof(DSRTInt8);

    // Return the value.
    return value;
}

void dsrt_pack_int8(DSRTSeeker *seeker, const DSRTInt8 value) {
    // Write the value directly to the buffer.
    *(DSRTInt8 *) (seeker->buffer.data + seeker->position) = dsrt_ensure_int8(value);

    // Update the position.
    seeker->position += sizeof(DSRTInt8);
}

DSRTInt16 dsrt_unpack_int16(DSRTSeeker *seeker) {
    // Read the value directly from the buffer.
    const DSRTInt16 value = dsrt_ensure_int16(*(DSRTInt16 *) (seeker->buffer.data + seeker->position));

    // Update the position.
    seeker->position += sizeof(DSRTInt16);

    // Return the value.
    return value;
}

void dsrt_pack_int16(DSRTSeeker *seeker, const DSRTInt16 value) {
    // Write the value directly to the buffer.
    *(DSRTInt16 *) (seeker->buffer.data + seeker->position) = dsrt_ensure_int16(value);

    // Update the position.
    seeker->position += sizeof(DSRTInt16);
}

DSRTInt32 dsrt_unpack_int32(DSRTSeeker *seeker) {
    // Read the value directly from the buffer.
    const DSRTInt32 value = dsrt_ensure_int32(*(DSRTInt32 *) (seeker->buffer.data + seeker->position));

    // Update the position.
    seeker->position += sizeof(DSRTInt32);

    // Return the value.
    return value;
}

void dsrt_pack_int32(DSRTSeeker *seeker, const DSRTInt32 value) {
    // Write the value directly to the buffer.
    *(DSRTInt32 *) (seeker->buffer.data + seeker->position) = dsrt_ensure_int32(value);

    // Update the position.
    seeker->position += sizeof(DSRTInt32);
}

DSRTInt64 dsrt_unpack_int64(DSRTSeeker *seeker) {
    // Read the value directly from the buffer.
    const DSRTInt64 value = dsrt_ensure_int64(*(DSRTInt64 *) (seeker->buffer.data + seeker->position));

    // Update the position.
    seeker->position += sizeof(DSRTInt64);

    // Return the value.
    return value;
}

void dsrt_pack_int64(DSRTSeeker *seeker, const DSRTInt64 value) {
    // Write the value directly to the buffer.
    *(DSRTInt64 *) (seeker->buffer.data + seeker->position) = dsrt_ensure_int64(value);

    // Update the position.
    seeker->position += sizeof(DSRTInt64);
}

DSRTNat8 dsrt_unpack_nat8(DSRTSeeker *seeker) {
    // Read the value directly from the buffer.
    const DSRTNat8 value = dsrt_ensure_nat8(*(DSRTNat8 *) (seeker->buffer.data + seeker->position));

    // Update the position.
    seeker->position += sizeof(DSRTNat8);

    // Return the value.
    return value;
}

void dsrt_pack_nat8(DSRTSeeker *seeker, const DSRTNat8 value) {
    // Write the value directly to the buffer.
    *(DSRTNat8 *) (seeker->buffer.data + seeker->position) = dsrt_ensure_nat8(value);

    // Update the position.
    seeker->position += sizeof(DSRTNat8);
}

DSRTNat16 dsrt_unpack_nat16(DSRTSeeker *seeker) {
    // Read the value directly from the buffer.
    const DSRTNat16 value = dsrt_ensure_nat16(*(DSRTNat16 *) (seeker->buffer.data + seeker->position));

    // Update the position.
    seeker->position += sizeof(DSRTNat16);

    // Return the value.
    return value;
}

void dsrt_pack_nat16(DSRTSeeker *seeker, const DSRTNat16 value) {
    // Write the value directly to the buffer.
    *(DSRTNat16 *) (seeker->buffer.data + seeker->position) = dsrt_ensure_nat16(value);

    // Update the position.
    seeker->position += sizeof(DSRTNat16);
}

DSRTNat32 dsrt_unpack_nat32(DSRTSeeker *seeker) {
    // Read the value directly from the buffer.
    const DSRTNat32 value = dsrt_ensure_nat32(*(DSRTNat32 *) (seeker->buffer.data + seeker->position));

    // Update the position.
    seeker->position += sizeof(DSRTNat32);

    // Return the value.
    return value;
}

void dsrt_pack_nat32(DSRTSeeker *seeker, const DSRTNat32 value) {
    // Write the value directly to the buffer.
    *(DSRTNat32 *) (seeker->buffer.data + seeker->position) = dsrt_ensure_nat32(value);

    // Update the position.
    seeker->position += sizeof(DSRTNat32);
}

DSRTNat64 dsrt_unpack_nat64(DSRTSeeker *seeker) {
    // Read the value directly from the buffer.
    const DSRTNat64 value = dsrt_ensure_nat64(*(DSRTNat64 *) (seeker->buffer.data + seeker->position));

    // Update the position.
    seeker->position += sizeof(DSRTNat64);

    // Return the value.
    return value;
}

void dsrt_pack_nat64(DSRTSeeker *seeker, const DSRTNat64 value) {
    // Write the value directly to the buffer.
    *(DSRTNat64 *) (seeker->buffer.data + seeker->position) = dsrt_ensure_nat64(value);

    // Update the position.
    seeker->position += sizeof(DSRTNat64);
}

DSRTFloat32 dsrt_unpack_float32(DSRTSeeker *seeker) {
    // Read the value directly from the buffer.
    const DSRTFloat32 value = dsrt_ensure_float32(*(DSRTFloat32 *) (seeker->buffer.data + seeker->position));

    // Update the position.
    seeker->position += sizeof(DSRTFloat32);

    // Return the value.
    return value;
}

void dsrt_pack_float32(DSRTSeeker *seeker, const DSRTFloat32 value) {
    // Write the value directly to the buffer.
    *(DSRTFloat32 *) (seeker->buffer.data + seeker->position) = dsrt_ensure_float32(value);

    // Update the position.
    seeker->position += sizeof(DSRTFloat32);
}

DSRTFloat64 dsrt_unpack_float64(DSRTSeeker *seeker) {
    // Read the value directly from the buffer.
    const DSRTFloat64 value = dsrt_ensure_float64(*(DSRTFloat64 *) (seeker->buffer.data + seeker->position));

    // Update the position.
    seeker->position += sizeof(DSRTFloat64);

    // Return the value.
    return value;
}

void dsrt_pack_float64(DSRTSeeker *seeker, const DSRTFloat64 value) {
    // Write the value directly to the buffer.
    *(DSRTFloat64 *) (seeker->buffer.data + seeker->position) = dsrt_ensure_float64(value);

    // Update the position.
    seeker->position += sizeof(DSRTFloat64);
}

void dsrt_copy_section_from_array(DSRTSeeker *dest_writer, const DSRTBuffer src, const DSRTSize size, const DSRTIndex start,
    const DSRTIndex end) {
    // Check the bounds.
    if (start > end || end > src.size) {
        dsrt_error(DSRT_BAD_INDEX);
        return;
    }

    // Check the source buffer.
    if (src.data == NULL) {
        dsrt_error(DSRT_NULL_POINTER);
        return;
    }

    // Write the data.
    dsrt_seeker_write(dest_writer, (DSRTBuffer) {(end - start) * size, src.data + start * size});
}

