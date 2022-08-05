cmake_minimum_required(VERSION 3.22)
project(memhack C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#add_compile_definitions(MH_BUILD_STATIC)
add_compile_definitions(MH_BUILD_DYNAMIC)

include_directories(../include)
include_directories(../include/memhack)

add_library(memhack_static STATIC
        ../include/memhack/error.h
        ../include/memhack/debug.h
        ../include/memhack/linkage.h
        ../include/memhack/memhack.h
        ../src/arch/windows/memhack_windows.c
        ../src/error.c
        ../src/memhack.c)

add_library(memhack_dynamic SHARED
        ../include/memhack/error.h
        ../include/memhack/debug.h
        ../include/memhack/linkage.h
        ../include/memhack/memhack.h
        ../src/arch/windows/memhack_windows.c
        ../src/error.c
        ../src/memhack.c)
