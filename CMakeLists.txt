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

if(WIN32)
    if(NOT MSVC)
        message(FATAL_ERROR "Please configure your build to use the MSVC compiler on Windows.")
    endif()
else()
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(FATAL_ERROR "MSVC is not supported on non-Windows platforms. Please use GCC.")
    endif()
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(src)
add_subdirectory(tests)

include(CTest)

add_test(NAME dsrt COMMAND test-dsrt)

# TODO: Add installer
