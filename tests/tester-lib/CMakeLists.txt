#[=======================================================================[
Copyright (C) 2024-2025 Gianmarco Lenzi
Licensed under MIT as part of the DSK Project, see LICENSE file for details.
A copy of the license can be found at: https://opensource.org/licenses/MIT.

CMakeLists.txt
Build the tester library.
#]=======================================================================]

add_library(tester-lib STATIC
        all.hpp
        common.hpp
        logging.cpp
        logging.hpp
        Tester.cpp
        Tester.hpp
        Test.cpp
        Test.hpp
        TestResults.hpp
        ModuleResults.hpp
)