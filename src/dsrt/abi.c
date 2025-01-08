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

DSRTList dsrt_list_new(const DSRTSize element_size, const DSRTSize count) {
    DSRTList list = {element_size, 0, 1, malloc(element_size)};

    if (list.data == NULL) {
        dsrt_error(DSRT_OUT_OF_MEMORY);
        return (DSRTList) {};
    }

    dsrt_list_resize(&list, count);

    memset(list.data, 0, list.element_size * list.count);

    return list;
}

void dsrt_list_resize(DSRTList *list, const DSRTSize count) {
    if (count == 0) {
        list->count = 0;
        return;
    }

    if (list->capacity < count || count < list->capacity / 2) {
        DSRTSize capacity = 1;

        while (capacity < count) {
            capacity *= 2;
        }

        dsrt_list_reserve(list, capacity);
    }

    list->count = count;
}

void dsrt_list_reserve(DSRTList *list, const DSRTSize capacity) {
    if (capacity == 0) {
        return;
    }

    if (list->count > capacity) {
        dsrt_error(DSRT_BAD_SIZE_ARG);
        return;
    }

    void *new_data = realloc(list->data, capacity * list->element_size);

    if (new_data == NULL) {
        dsrt_error(DSRT_OUT_OF_MEMORY);
        return;
    }

    list->data = new_data;
    list->capacity = capacity;
}

void dsrt_list_append(DSRTList *list, const void *value) {
    dsrt_list_resize(list, list->count + 1);
    dsrt_list_set(*list, list->count - 1, value);
}

void dsrt_list_pop_to(DSRTList *list, void *dest) {
    if (list->count > 0) {
        memcpy(dest, dsrt_list_get(*list, list->count - 1), list->element_size);
        list->count--;
        dsrt_list_resize(list, list->count);
        return;
    }

    dsrt_error(DSRT_BAD_INDEX);
}

void *dsrt_list_get(const DSRTList list, const DSRTSize index) {
    if (index < list.count) {
        return list.data + index * list.element_size;
    }

    dsrt_error(DSRT_BAD_INDEX);
    return NULL;
}

void dsrt_list_set(const DSRTList list, const DSRTSize index, const void *value) {
    if (index < list.count) {
        memcpy(list.data + index * list.element_size, value, list.element_size);
        return;
    }

    dsrt_error(DSRT_BAD_INDEX);
}

void dsrt_list_free(const DSRTList list) {
    free(list.data);
}

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

DSRTSize dsrt_get_ctype_descriptor_type_args(const DSRTCTypeDescriptor ctype_descriptor) {
    switch (ctype_descriptor.type) {
        case DSRT_CTYPE_SIMPLE:
            return 0;
        case DSRT_CTYPE_ARRAY:
            return 1;
        case DSRT_CTYPE_STRUCT:
            return ctype_descriptor.descriptor.as_struct.num;
    }

    return 0;
}

DSRTSize dsrt_get_ctype_descriptor_simple_size(const DSRTCTypeDescriptorSimple ctype_descriptor) {
    switch (ctype_descriptor.kind) {
        case DSRT_KIND_INT:
            switch (ctype_descriptor.size.width) {
                case DSRT_WIDTH8:
                    return sizeof(DSRTInt8);
                case DSRT_WIDTH16:
                    return sizeof(DSRTInt16);
                case DSRT_WIDTH32:
                    return sizeof(DSRTInt32);
                case DSRT_WIDTH64:
                    return sizeof(DSRTInt64);
            }
        case DSRT_KIND_NAT:
            switch (ctype_descriptor.size.width) {
                case DSRT_WIDTH8:
                    return sizeof(DSRTNat8);
                case DSRT_WIDTH16:
                    return sizeof(DSRTNat16);
                case DSRT_WIDTH32:
                    return sizeof(DSRTNat32);
                case DSRT_WIDTH64:
                    return sizeof(DSRTNat64);
            }
        case DSRT_KIND_FLOAT:
            switch (ctype_descriptor.size.float_width) {
                case DSRT_FLOAT_WIDTH32:
                    return sizeof(DSRTFloat32);
                case DSRT_FLOAT_WIDTH64:
                    return sizeof(DSRTFloat64);
            }
        case DSRT_KIND_SIZE:
            return sizeof(DSRTSize);
    }

    return 0;
}

typedef struct {
    enum {
        SIMPLE,
        ARRAY,
        STRUCT
    } type;

    union {
        DSRTSize size;
        DSRTSize num;
    };
} Token;

DSRTSize dsrt_get_ctype_descriptor_size(const DSRTCTypeDescriptor ctype_descriptor) {
    DSRTList stack = dsrt_list_new(sizeof(Token), 0);
    DSRTList descriptor_stack = dsrt_list_new(sizeof(DSRTCTypeDescriptor), 1);

    dsrt_list_set(descriptor_stack, 0, &ctype_descriptor);

    while (descriptor_stack.count > 0) {
        DSRTCTypeDescriptor top_descriptor;
        dsrt_list_pop_to(&descriptor_stack, &top_descriptor);

        switch (top_descriptor.type) {
            case DSRT_CTYPE_SIMPLE:
                const Token token = {SIMPLE, {dsrt_get_ctype_descriptor_simple_size(top_descriptor.descriptor.as_simple)}};
                dsrt_list_append(&stack, &token);
                break;
            case DSRT_CTYPE_ARRAY:
                const Token array_token = {ARRAY, {top_descriptor.descriptor.as_array.num}};
                dsrt_list_append(&stack, &array_token);
                dsrt_list_append(&descriptor_stack, top_descriptor.descriptor.as_array.element_type);
                break;
            case DSRT_CTYPE_STRUCT:
                const Token struct_token = {STRUCT, {top_descriptor.descriptor.as_struct.num}};
                dsrt_list_append(&stack, &struct_token);

                for (DSRTSize i = 0; i < top_descriptor.descriptor.as_struct.num; i++) {
                    dsrt_list_append(&descriptor_stack, &top_descriptor.descriptor.as_struct.element_types[i]);
                }

                break;
            default:
                break;
        }
    }

    dsrt_list_free(descriptor_stack);

    DSRTList operands = dsrt_list_new(sizeof(DSRTSize), 0);

    for (DSRTSize i = 0; i < stack.count; i++) {
        const DSRTSize j = stack.count - i - 1;

        const Token token = *(Token *) dsrt_list_get(stack, j);

        switch (token.type) {
            case SIMPLE:
                dsrt_list_append(&operands, &token.size);
                break;
            case ARRAY:
                DSRTSize array_size;
                dsrt_list_pop_to(&operands, &array_size);
                array_size *= token.num;
                dsrt_list_append(&operands, &array_size);
                break;
            case STRUCT:
                DSRTSize struct_size = 0;

                for (DSRTSize k = 0; k < token.num; k++) {
                    DSRTSize temp;
                    dsrt_list_pop_to(&operands, &temp);
                    struct_size += temp;
                }

                dsrt_list_append(&operands, &struct_size);
                break;
        }
    }

    DSRTSize result;
    dsrt_list_pop_to(&operands, &result);

    dsrt_list_free(operands);
    dsrt_list_free(stack);

    return result;
}
