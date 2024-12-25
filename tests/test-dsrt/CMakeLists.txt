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
        test-memory/common.hpp
        test-memory/all.hpp
        test-memory/SimpleSingle.cpp
        test-memory/SimpleSingle.hpp
        test-dsrt/MemoryTester.hpp
        test-dsrt/common.hpp
        test-dsrt/all.hpp
        DSRTTester.hpp)

target_link_libraries(test-dsrt PRIVATE
        dsrt
        tester-lib)