#[=======================================================================[
Copyright (C) 2024-2025 Gianmarco Lenzi
Licensed under MIT as part of the DSK Project, see LICENSE file for details.
A copy of the license can be found at: https://opensource.org/licenses/MIT.

CMakeLists.txt
Build the DSRT tester.
#]=======================================================================]

add_executable(test-dsrt
        main.cpp
        main.hpp
        common.hpp
        DSRTTester.hpp
        test-memory/common.hpp
        test-memory/simple_single.cpp
        test-abi/common.hpp
        test-abi/array_copy.cpp
        test-abi/pack_unpack.cpp
        test-abi/ctype.cpp
)

target_link_libraries(test-dsrt PRIVATE
        dsrt
        tester-lib
)