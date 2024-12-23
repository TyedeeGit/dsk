#[=======================================================================[
Copyright (C) 2024-2025 Gianmarco Lenzi
Licensed under MIT as part of the DSK Project, see LICENSE file for details.
A copy of the license can be found at: https://opensource.org/licenses/MIT.

CMakeLists.txt
Build the tests.
#]=======================================================================]

add_executable(tests
        Logging/common.hpp
        Logging/logging.cpp
        Logging/logging.hpp
)

target_link_libraries(tests PRIVATE dsrt)
