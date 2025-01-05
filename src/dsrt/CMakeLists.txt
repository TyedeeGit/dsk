#[=======================================================================[
Copyright (C) 2024-2025 Gianmarco Lenzi
Licensed under MIT as part of the DSK Project, see LICENSE file for details.
A copy of the license can be found at: https://opensource.org/licenses/MIT.

CMakeLists.txt
Build the DSRT library.
#]=======================================================================]

add_library(dsrt SHARED
        main.c
        common.h
        dsrt_memory.c
        dsrt_memory.h
        err.c
        err.h
        abi.c
        abi.h
)
