/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 *
 * @file PackUnpack.cpp
 * @author Gianmarco Lenzi
 * @brief 
 */

#include "PackUnpack.hpp"
#include "../../../src/dsrt/abi.h"

namespace TestDSRT::TestABI {
    void PackUnpack::run() const {
        const DSRTBuffer buffer = dsrt_alloc_buffer(100);
        DSRTSeeker reader = dsrt_seeker_new(buffer);
        DSRTSeeker writer = dsrt_seeker_new(buffer);

        // Declare an Int8
        constexpr DSRTInt8 int8 = 42;

        // Pack it
        dsrt_pack_int8(&writer, int8);

        if (dsrt_unpack_int8(&reader) != int8) {
            // If unpacking does not get the same value, free the buffer and fail.
            dsrt_free_buffer(buffer);
            this->fail("Failed to unpack int8.");
            return;
        }

        // Declare an Int16
        constexpr DSRTInt16 int16 = 42;

        // Pack it
        dsrt_pack_int16(&writer, int16);

        if (dsrt_unpack_int16(&reader) != int16) {
            // If unpacking does not get the same value, free the buffer and fail.
            dsrt_free_buffer(buffer);
            this->fail("Failed to unpack int16.");
            return;
        }

        constexpr DSRTInt32 int32 = 42;

        // Pack it
        dsrt_pack_int32(&writer, int32);

        if (dsrt_unpack_int32(&reader) != int32) {
            // If unpacking does not get the same value, free the buffer and fail.
            dsrt_free_buffer(buffer);
            this->fail("Failed to unpack int32.");
            return;
        }

        // Declare an Int64
        constexpr DSRTInt64 int64 = 42;

        // Pack it
        dsrt_pack_int64(&writer, int64);

        if (dsrt_unpack_int64(&reader) != int64) {
            // If unpacking does not get the same value, free the buffer and fail.
            dsrt_free_buffer(buffer);
            this->fail("Failed to unpack int64.");
            return;
        }

        // Declare a Nat8
        constexpr DSRTNat8 nat8 = 42;

        // Pack it
        dsrt_pack_nat8(&writer, nat8);

        if (dsrt_unpack_nat8(&reader) != nat8) {
            // If unpacking does not get the same value, free the buffer and fail.
            dsrt_free_buffer(buffer);
            this->fail("Failed to unpack nat8.");
            return;
        }

        // Declare a Nat16
        constexpr DSRTNat16 nat16 = 42;

        // Pack it
        dsrt_pack_nat16(&writer, nat16);

        if (dsrt_unpack_nat16(&reader) != nat16) {
            // If unpacking does not get the same value, free the buffer and fail.
            dsrt_free_buffer(buffer);
            this->fail("Failed to unpack nat16.");
            return;
        }

        // Declare a Nat32
        constexpr DSRTNat32 nat32 = 42;

        // Pack it
        dsrt_pack_nat32(&writer, nat32);

        if (dsrt_unpack_nat32(&reader) != nat32) {
            // If unpacking does not get the same value, free the buffer and fail.
            dsrt_free_buffer(buffer);
            this->fail("Failed to unpack nat32.");
            return;
        }

        // Declare a Nat64
        constexpr DSRTNat64 nat64 = 42;

        // Pack it
        dsrt_pack_nat64(&writer, nat64);

        if (dsrt_unpack_nat64(&reader) != nat64) {
            // If unpacking does not get the same value, free the buffer and fail.
            dsrt_free_buffer(buffer);
            this->fail("Failed to unpack nat64.");
            return;
        }

        // Declare a Float32
        constexpr DSRTFloat32 float32 = 42.0f;

        // Pack it
        dsrt_pack_float32(&writer, float32);

        if (dsrt_unpack_float32(&reader) != float32) {
            // If unpacking does not get the same value, free the buffer and fail.
            dsrt_free_buffer(buffer);
            this->fail("Failed to unpack float32.");
            return;
        }

        // Declare a Float64
        constexpr DSRTFloat64 float64 = 42.0;

        // Pack it
        dsrt_pack_float64(&writer, float64);

        if (dsrt_unpack_float64(&reader) != float64) {
            // If unpacking does not get the same value, free the buffer and fail.
            dsrt_free_buffer(buffer);
            this->fail("Failed to unpack float64.");
            return;
        }

        dsrt_free_buffer(buffer);
    }

} // TestDSRT::TestABI
