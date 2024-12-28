#[=======================================================================[
Copyright (C) 2024-2025 Gianmarco Lenzi
Licensed under MIT as part of the DSK Project, see LICENSE file for details.
A copy of the license can be found at: https://opensource.org/licenses/MIT.

CMakeLists.txt
Build the tester library.
#]=======================================================================]

add_library(tester-lib SHARED
        all.hpp
        common.hpp
        logging.cpp
        logging.hpp
        Tester.cpp
        Tester.hpp
        UnitTester.hpp
        TestResults.hpp
        ModuleResults.hpp
        ModuleTester.cpp
        ModuleTester.hpp
        ComponentTester.cpp
        ComponentTester.hpp
        ComponentResults.hpp
)

find_path(TERMCOLOR_INCLUDE_DIRS "termcolor/termcolor.hpp")
target_include_directories(tester-lib PRIVATE ${TERMCOLOR_INCLUDE_DIRS})
