#[=======================================================================[
Copyright (C) 2024-2025 Gianmarco Lenzi
Licensed under MIT as part of the DSK Project, see LICENSE file for details.
A copy of the license can be found at: https://opensource.org/licenses/MIT.

tests/CMakeLists.txt
Build the tests.
#]=======================================================================]

add_executable(tests
        common.hpp
        main.cpp
        main.hpp
        Logging/common.hpp
        Logging/logging.cpp
        Logging/logging.hpp
        TestDSRT/MemTest.cpp
        TestDSRT/MemTest.hpp
        TestDSRT/common.hpp
        TestDSRT/all.hpp
)

target_link_libraries(tests PRIVATE dsrt)
