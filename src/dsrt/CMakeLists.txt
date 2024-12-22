#[=======================================================================[
Copyright (C) 2024-2025 Gianmarco Lenzi
Licensed under MIT as part of the DSK Project, see LICENSE file for details.
A copy of the license can be found at: https://opensource.org/licenses/MIT.

src/dsrt/CMakeLists.txt
Build the DSRT library.
#]=======================================================================]

add_library(dsrt STATIC
        main.c
        main.h
        common.h
        dsrt_memory.c
        dsrt_memory.h
)
