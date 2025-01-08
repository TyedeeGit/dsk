/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file abi.h
 * @author Gianmarco Lenzi
 * @brief Header for the DSRT ABI helpers.
 */

#pragma once
#include "common.h"
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
    #define SWAP_UINT16(val) _byteswap_ushort(val)
    #define SWAP_UINT32(val) _byteswap_ulong(val)
    #define SWAP_UINT64(val) _byteswap_uint64(val)
#elif defined(__GNUC__)
    #define SWAP_UINT16(val) __builtin_bswap16(val)
    #define SWAP_UINT32(val) __builtin_bswap32(val)
    #define SWAP_UINT64(val) __builtin_bswap64(val)
#else
    #error "Unsupported compiler"
#endif

#define SWAP_INT16(val) SWAP_UINT16(val)
#define SWAP_INT32(val) SWAP_UINT32(val)
#define SWAP_INT64(val) SWAP_UINT64(val)

#define SWAP_FLOAT32(val) SWAP_UINT32(val)
#define SWAP_FLOAT64(val) SWAP_UINT64(val)

inline bool dsrt_is_little_endian(void) { uint16_t test = 1; return *(uint8_t *) &test == 1; }

/**
 * @brief A buffer of memory.
 */
typedef struct {
    /**
     * @brief The size of the buffer in bytes.
     */
    DSRTSize size;

    /**
     * @brief The data in the buffer.
     */
    char *data;
} DSRTBuffer;

/**
 * @brief A list of elements.
 */
typedef struct {
    /**
     * @brief The size of each element in the list.
     */
    DSRTSize element_size;

    /**
     * @brief The number of elements in the list.
     */
    DSRTSize count;

    /**
     * @brief The capacity of the list.
     */
    DSRTSize capacity;

    /**
     * @brief The data in the list.
     */
    char *data;
} DSRTList;

/**
 * @brief Allocates a new DSRTList with the given element size.
 * @details The new list will have a capacity of 1 and will be empty.
 * @param element_size The size of each element in the list.
 * @param count
 * @return A newly allocated DSRTList.
 */
DSRTList dsrt_list_new(DSRTSize element_size, DSRTSize count);

/**
 * @brief Resizes a DSRTList to the given length.
 * @param list The list to resize.
 * @param count The new length of the list.
 * @return The reallocated DSRTList.
 */
void dsrt_list_resize(DSRTList *list, DSRTSize count);

/**
 * @brief Reserves space in a DSRTList for the given number of elements.
 * @param list The list to reserve space in.
 * @param capacity The number of elements to reserve space for.
 */
void dsrt_list_reserve(DSRTList *list, DSRTSize capacity);

/**
 * @brief Appends an element to the end of a DSRTList.
 * @param list The DSRTList to append to.
 * @param value The value to append.
 */
void dsrt_list_append(DSRTList *list, const void *value);

/**
 * @brief Removes and returns the last element from a DSRTList.
 * @param list The DSRTList to pop the element from.
 * @param dest
 * @return The popped element, or NULL if the list is empty.
 */
void dsrt_list_pop_to(DSRTList *list, void *dest);

/**
 * @brief Gets an element from a DSRTList.
 * @param list The DSRTList to get the element from.
 * @param index The index of the element to get.
 * @return The element at the given index.
 */
void *dsrt_list_get(DSRTList list, DSRTSize index);

/**
 * @brief Sets an element in a DSRTList.
 * @param list The DSRTList to set the element in.
 * @param index The index of the element to set.
 * @param value The value to set.
 */
void dsrt_list_set(DSRTList list, DSRTSize index, const void *value);

/**
 * @brief Frees a DSRTList.
 * @param list The DSRTList to free.
 */
void dsrt_list_free(DSRTList list);

/**
 * @brief A seeker for a buffer.
 */
typedef struct {
    /**
     * @brief The buffer to read from.
     */
    DSRTBuffer buffer;

    /**
     * @brief The current position in the buffer.
     */
    DSRTSize position;
} DSRTSeeker;

/**
 * @brief Allocate a buffer of the specified size.
 * @param size The size of the buffer to allocate.
 * @return A DSRTBuffer containing the allocated memory.
 */
DSRTBuffer dsrt_alloc_buffer(DSRTSize size);

/**
 * @brief Resize a buffer to the specified size.
 * @param buffer The buffer to resize. The pointer to the buffer is modified
 * to point to the new memory location after resizing.
 * @param size The new size of the buffer.
 */
void dsrt_realloc_buffer(DSRTBuffer *buffer, DSRTSize size);

/**
 * @brief Free a buffer.
 * @param buffer The buffer to free.
 */
void dsrt_free_buffer(DSRTBuffer buffer);

/**
 * @brief Copy the contents of a buffer to another buffer.
 * @param dest The destination buffer. The contents of this buffer are replaced
 * with the contents of the source buffer.
 * @param src The source buffer.
 * @param dest_offset
 * @param src_offset
 */
void dsrt_copy_buffer(DSRTBuffer dest, DSRTBuffer src, DSRTSize dest_offset, DSRTSize src_offset);

/**
 * @brief Create a seeker for a buffer.
 * @param buffer The buffer to create a seeker for.
 * @return A DSRTSeeker object.
 */
DSRTSeeker dsrt_seeker_new(DSRTBuffer buffer);

/**
 * @brief Read data from a buffer using a seeker.
 * @param seeker The seeker to read from.
 * @param size The size of the data to read.
 * @return A buffer containing the read data.
 */
DSRTBuffer dsrt_seeker_read(DSRTSeeker *seeker, DSRTSize size);

/**
 * @brief Write data from a buffer using a seeker.
 * @param seeker The seeker to write to.
 * @param buffer The buffer containing the data to write.
 * @note Ensure the seeker's destination buffer is large enough to hold the data.
 */
void dsrt_seeker_write(DSRTSeeker *seeker, DSRTBuffer buffer);

/**
 * @brief Resize a seeker's buffer.
 * @param seeker The seeker to resize.
 * @param size The new size of the buffer.
 */
void dsrt_seeker_resize(DSRTSeeker *seeker, DSRTSize size);

/**
 * @brief Set the position of a seeker.
 * @param seeker The seeker to set the position of.
 * @param position The new position of the seeker.
 */
void dsrt_seeker_goto(DSRTSeeker *seeker, DSRTSize position);

/**
 * @brief 8-bit signed integer.
 */
typedef int8_t  DSRTInt8;

/**
 * @brief Ensure the endianness of an 8-bit signed integer.
 * @param value The integer to ensure the endianness of.
 * @return An 8-bit signed integer with the correct endianness.
 */
inline DSRTInt8 dsrt_ensure_int8(const DSRTInt8 value) { return value; }

/**
 * @brief 16-bit signed integer.
 */
typedef int16_t DSRTInt16;

/**
 * @brief Ensure the endianness of a 16-bit signed integer.
 * @param value The integer to ensure the endianness of.
 * @return A 16-bit signed integer with the correct endianness.
 */
inline DSRTInt16 dsrt_ensure_int16(const DSRTInt16 value) {
    if (dsrt_is_little_endian()) return value;
    return SWAP_INT16(value);
}

/**
 * @brief 32-bit signed integer.
 */
typedef int32_t DSRTInt32;

/**
 * @brief Ensure the endianness of a 32-bit signed integer.
 * @param value The integer to ensure the endianness of.
 * @return A 32-bit signed integer with the correct endianness.
 */
inline DSRTInt32 dsrt_ensure_int32(const DSRTInt32 value) {
    if (dsrt_is_little_endian()) return value;
    return SWAP_INT32(value);
}

/**
 * @brief 64-bit signed integer.
 */
typedef int64_t DSRTInt64;

/**
 * @brief Ensure the endianness of a 64-bit signed integer.
 * @param value The integer to ensure the endianness of.
 * @return A 64-bit signed integer with the correct endianness.
 */
inline DSRTInt64 dsrt_ensure_int64(const DSRTInt64 value) {
    if (dsrt_is_little_endian()) return value;
    return SWAP_INT64(value);
}


/**
 * @brief Unpack an 8-bit signed integer from a buffer.
 * @param seeker The seeker to read from.
 * @return The unpacked integer.
 */
DSRTInt8 dsrt_unpack_int8(DSRTSeeker *seeker);

/**
 * @brief Pack an 8-bit signed integer into a buffer.
 * @param seeker The seeker to write to.
 * @param value The integer to pack.
 */
void dsrt_pack_int8(DSRTSeeker *seeker, DSRTInt8 value);

/**
 * @brief Unpack a 16-bit signed integer from a buffer.
 * @param seeker The seeker to read from.
 * @return The unpacked integer.
 */
DSRTInt16 dsrt_unpack_int16(DSRTSeeker *seeker);

/**
 * @brief Pack a 16-bit signed integer into a buffer.
 * @param seeker The seeker to write to.
 * @param value The integer to pack.
 */
void dsrt_pack_int16(DSRTSeeker *seeker, DSRTInt16 value);

/**
 * @brief Unpack a 32-bit signed integer from a buffer.
 * @param seeker The seeker to read from.
 * @return The unpacked integer.
 */
DSRTInt32 dsrt_unpack_int32(DSRTSeeker *seeker);

/**
 * @brief Pack a 32-bit signed integer into a buffer.
 * @param seeker The seeker to write to.
 * @param value The integer to pack.
 */
void dsrt_pack_int32(DSRTSeeker *seeker, DSRTInt32 value);

/**
 * @brief Unpack a 64-bit signed integer from a buffer.
 * @param seeker The seeker to read from.
 * @return The unpacked integer.
 */
DSRTInt64 dsrt_unpack_int64(DSRTSeeker *seeker);

/**
 * @brief Pack a 64-bit signed integer into a buffer.
 * @param seeker The seeker to write to.
 * @param value The integer to pack.
 */
void dsrt_pack_int64(DSRTSeeker *seeker, DSRTInt64 value);


/**
 * @brief 8-bit unsigned integer.
 */
typedef uint8_t  DSRTNat8;

/**
 * @brief Ensure the endianness of an 8-bit unsigned integer.
 * @param value The integer to ensure the endianness of.
 * @return An 8-bit unsigned integer with the correct endianness.
 */
inline DSRTNat8 dsrt_ensure_nat8(const DSRTNat8 value) { return value; }

/**
 * @brief 16-bit unsigned integer.
 */
typedef uint16_t DSRTNat16;

/**
 * @brief Ensure the endianness of a 16-bit unsigned integer.
 * @param value The integer to ensure the endianness of.
 * @return A 16-bit unsigned integer with the correct endianness.
 */
inline DSRTNat16 dsrt_ensure_nat16(const DSRTNat16 value) {
    if (dsrt_is_little_endian()) return value;
    return SWAP_UINT16(value);
}

/**
 * @brief 32-bit unsigned integer.
 */
typedef uint32_t DSRTNat32;

/**
 * @brief Ensure the endianness of a 32-bit unsigned integer.
 * @param value The integer to ensure the endianness of.
 * @return A 32-bit unsigned integer with the correct endianness.
 */
inline DSRTNat32 dsrt_ensure_nat32(const DSRTNat32 value) {
    if (dsrt_is_little_endian()) return value;
    return SWAP_UINT32(value);
}

/**
 * @brief 64-bit unsigned integer.
 */
typedef uint64_t DSRTNat64;

/**
 * @brief Ensure the endianness of a 64-bit unsigned integer.
 * @param value The integer to ensure the endianness of.
 * @return A 64-bit unsigned integer with the correct endianness.
 */
inline DSRTNat64 dsrt_ensure_nat64(const DSRTNat64 value) {
    if (dsrt_is_little_endian()) return value;
    return SWAP_UINT64(value);
}


/**
 * @brief Unpack an unsigned integer from a buffer.
 * @param seeker The seeker to read from.
 * @return The unpacked unsigned integer.
 */
DSRTNat8 dsrt_unpack_nat8(DSRTSeeker *seeker);

/**
 * @brief Pack an 8-bit unsigned integer into a buffer.
 * @param seeker The seeker to write to.
 * @param value The 8-bit unsigned integer to pack.
 */
void dsrt_pack_nat8(DSRTSeeker *seeker, DSRTNat8 value);

/**
 * @brief Unpack an unsigned integer from a buffer.
 * @param seeker The seeker to read from.
 * @return The unpacked 16-bit unsigned integer.
 */
DSRTNat16 dsrt_unpack_nat16(DSRTSeeker *seeker);

/**
 * @brief Pack a 16-bit unsigned integer into a buffer.
 * @param seeker The seeker to write to.
 * @param value The 16-bit unsigned integer to pack.
 */
void dsrt_pack_nat16(DSRTSeeker *seeker, DSRTNat16 value);

/**
 * @brief Unpack a natural number from a buffer.
 * @param seeker The seeker to read from.
 * @return The unpacked natural number.
 */
DSRTNat32 dsrt_unpack_nat32(DSRTSeeker *seeker);

/**
 * @brief Pack a natural number into a buffer.
 * @param seeker The seeker to write to.
 * @param value The natural number to pack.
 */
void dsrt_pack_nat32(DSRTSeeker *seeker, DSRTNat32 value);

/**
 * @brief Unpack a natural number from a buffer.
 * @param seeker The seeker to read from.
 * @return The unpacked natural number.
 */
DSRTNat64 dsrt_unpack_nat64(DSRTSeeker *seeker);

/**
 * @brief Pack a natural number into a buffer.
 * @param seeker The seeker to write to.
 * @param value The natural number to pack.
 */
void dsrt_pack_nat64(DSRTSeeker *seeker, DSRTNat64 value);

/**
 * @brief 32-bit floating point type.
 */
typedef float  DSRTFloat32;

/**
 * @brief Ensure the endianness of a 32-bit floating point number.
 * @param value The floating point number to ensure the endianness of.
 * @return A 32-bit floating point number with the correct endianness.
 */
inline DSRTFloat32 dsrt_ensure_float32(const DSRTFloat32 value) {
    if (dsrt_is_little_endian()) return value;
    return SWAP_FLOAT32(value);
}

/**
 * @brief 64-bit floating point type.
 */
typedef double DSRTFloat64;

/**
 * @brief Ensure the endianness of a 64-bit floating point number.
 * @param value The floating point number to ensure the endianness of.
 * @return A 64-bit floating point number with the correct endianness.
 */
inline DSRTFloat64 dsrt_ensure_float64(const DSRTFloat64 value) {
    if (dsrt_is_little_endian()) return value;
    return SWAP_FLOAT64(value);
}

/**
 * @brief Unpack a 32-bit floating point number from a buffer.
 * @param seeker The seeker to read from.
 * @return The unpacked floating point number.
 */
DSRTFloat32 dsrt_unpack_float32(DSRTSeeker *seeker);

/**
 * @brief Pack a 32-bit floating point number into a buffer.
 * @param seeker The seeker to write to.
 * @param value The floating point number to pack.
 */
void dsrt_pack_float32(DSRTSeeker *seeker, DSRTFloat32 value);

/**
 * @brief Unpack a 64-bit floating point number from a buffer.
 * @param seeker The seeker to read from.
 * @return The unpacked floating point number.
 */
DSRTFloat64 dsrt_unpack_float64(DSRTSeeker *seeker);

/**
 * @brief Pack a 64-bit floating point number into a buffer.
 * @param seeker The seeker to write to.
 * @param value The floating point number to pack.
 */
void dsrt_pack_float64(DSRTSeeker *seeker, DSRTFloat64 value);

/**
 * @brief Copy a section from an array to a destination buffer.
 * @param dest_writer The destination seeker.
 * @param src The source buffer.
 * @param size The size of the section.
 * @param start The start index of the section.
 * @param end The end index of the section.
 */
void dsrt_copy_section_from_array(DSRTSeeker *dest_writer, DSRTBuffer src, DSRTSize size, DSRTIndex start,
                                  DSRTIndex end);

struct DSRTCTypeDescriptor_;

/**
 * @brief The width of a simple type.
 */
typedef enum {
    /**
     * @brief 8-bit width.
     */
    DSRT_WIDTH8 = 0,
    /**
     * @brief 16-bit width.
     */
    DSRT_WIDTH16 = 1,
    /**
     * @brief 32-bit width.
     */
    DSRT_WIDTH32 = 2,
    /**
     * @brief 64-bit width.
     */
    DSRT_WIDTH64 = 3
} DSRTWidth;

/**
 * @brief The width of a simple floating point type.
 */
typedef enum {
    /**
     * @brief 32-bit floating point width.
     */
    DSRT_FLOAT_WIDTH32 = 0,
    /**
     * @brief 64-bit floating point width.
     */
    DSRT_FLOAT_WIDTH64 = 1
} DSRTFloatWidth;

/**
 * @brief The kind of simple type.
 */
typedef enum {
    /**
     * @brief Signed integer type.
     */
    DSRT_KIND_INT = 0,
    /**
     * @brief Unsigned integer type.
     */
    DSRT_KIND_NAT = 1,
    /**
     * @brief Size type.
     */
    DSRT_KIND_SIZE = 2,
    /**
     * @brief Floating point type.
     */
    DSRT_KIND_FLOAT = 3
} DSRTSimpleKind;

/**
 * @brief The type of complex type descriptor.
 */
typedef enum {
    /**
     * @brief The type descriptor is a simple type.
     */
    DSRT_CTYPE_SIMPLE = 0,
    /**
     * @brief The type descriptor is an array type.
     */
    DSRT_CTYPE_ARRAY = 1,
    /**
     * @brief The type descriptor is a struct type.
     */
    DSRT_CTYPE_STRUCT = 2
} DSRTCTypeDescriptorType;

/**
 * @brief The type of simple type.
 */
typedef struct {
    /**
     * @brief The kind of simple type.
     */
    DSRTSimpleKind kind;

    /**
     * @brief The width of the simple type.
     */
    union {
        /**
         * @brief The width of an integer type.
         */
        DSRTWidth width;

        /**
         * @brief The width of a floating point type.
         */
        DSRTFloatWidth float_width;
    } size;
} DSRTCTypeDescriptorSimple;

/**
 * @brief The type of array type.
 */
typedef struct {
    /**
     * @brief The number of elements in the array.
     */
    DSRTSize num;

    /**
     * @brief The type of the elements in the array.
     */
    const struct DSRTCTypeDescriptor_ *element_type;
} DSRTCTypeDescriptorArray;

/**
 * @brief The type of struct type.
 */
typedef struct {
    /**
     * @brief The number of elements in the struct.
     */
    DSRTSize num;

    /**
     * @brief The types of the elements in the struct.
     */
    const struct DSRTCTypeDescriptor_ *element_types;
} DSRTCTypeDescriptorStruct;

/**
 * @brief A ctype descriptor.
 */
typedef struct DSRTCTypeDescriptor_ {
    /**
     * @brief The kind of the complex type descriptor.
     */
    DSRTCTypeDescriptorType type;

    /**
     * @brief The descriptor of the complex type.
     */
    union {
        /**
         * @brief The descriptor of a simple type.
         */
        DSRTCTypeDescriptorSimple as_simple;

        /**
         * @brief The descriptor of an array type.
         */
        DSRTCTypeDescriptorArray as_array;

        /**
         * @brief The descriptor of a struct type.
         */
        DSRTCTypeDescriptorStruct as_struct;
    } descriptor;
} DSRTCTypeDescriptor;

static DSRTCTypeDescriptor DSRT_NAT8 = {DSRT_CTYPE_SIMPLE, {DSRT_KIND_NAT,  {.width = DSRT_WIDTH8}}};
static DSRTCTypeDescriptor DSRT_NAT16 = {DSRT_CTYPE_SIMPLE, {DSRT_KIND_NAT, {.width = DSRT_WIDTH16}}};
static DSRTCTypeDescriptor DSRT_NAT32 = {DSRT_CTYPE_SIMPLE, {DSRT_KIND_NAT, {.width = DSRT_WIDTH32}}};
static DSRTCTypeDescriptor DSRT_NAT64 = {DSRT_CTYPE_SIMPLE, {DSRT_KIND_NAT, {.width = DSRT_WIDTH64}}};

static DSRTCTypeDescriptor DSRT_INT8 = {DSRT_CTYPE_SIMPLE, {DSRT_KIND_INT,  {.width = DSRT_WIDTH8}}};
static DSRTCTypeDescriptor DSRT_INT16 = {DSRT_CTYPE_SIMPLE, {DSRT_KIND_INT, {.width = DSRT_WIDTH16}}};
static DSRTCTypeDescriptor DSRT_INT32 = {DSRT_CTYPE_SIMPLE, {DSRT_KIND_INT, {.width = DSRT_WIDTH32}}};
static DSRTCTypeDescriptor DSRT_INT64 = {DSRT_CTYPE_SIMPLE, {DSRT_KIND_INT, {.width = DSRT_WIDTH64}}};

static DSRTCTypeDescriptor DSRT_FLOAT32 = {DSRT_CTYPE_SIMPLE, {DSRT_KIND_FLOAT, {.float_width = DSRT_FLOAT_WIDTH32}}};
static DSRTCTypeDescriptor DSRT_FLOAT64 = {DSRT_CTYPE_SIMPLE, {DSRT_KIND_FLOAT, {.float_width = DSRT_FLOAT_WIDTH64}}};

static DSRTCTypeDescriptor DSRT_SIZE = {DSRT_CTYPE_SIMPLE, {DSRT_KIND_SIZE, {}}};

/**
 * @brief Get the size of a packed ctype descriptor.
 * @details This function returns the size a packed ctype descriptor would take
 * up in memory. The size is the total size of all elements of the descriptor,
 * including the types of the elements of the descriptor.
 * @param ctype_descriptor The ctype descriptor to get the size of.
 * @return The size of the packed ctype descriptor.
 */
DSRTSize dsrt_get_ctype_descriptor_size(DSRTCTypeDescriptor ctype_descriptor);


/**
 * @brief Unpack a ctype descriptor from a buffer.
 * @param seeker The seeker to unpack from.
 * @return The unpacked ctype descriptor.
 */
DSRTCTypeDescriptor dsrt_unpack_ctype_descriptor(DSRTSeeker *seeker);


/**
 * @brief Pack a ctype descriptor into a buffer.
 * @param seeker The seeker to pack into.
 * @param ctype_descriptor The ctype descriptor to pack.
 */
void dsrt_pack_ctype_descriptor(DSRTSeeker *seeker, DSRTCTypeDescriptor ctype_descriptor);

#ifdef __cplusplus
}
#endif
