#[=======================================================================[
Copyright (C) 2024-2025 Gianmarco Lenzi
Licensed under MIT as part of the DSK project, see LICENSE file for details.
A copy of the license can be found at: https://opensource.org/licenses/MIT.

CMakeLists.txt
Build all components and their tests.
#]=======================================================================]

cmake_minimum_required(VERSION 3.28)
project(dsk)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(tests)

include(CTest)

add_test(NAME tests COMMAND tests)

# TODO: Add installer
