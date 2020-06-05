cmake_minimum_required(VERSION 3.15)
project(uchat C)

set(CMAKE_C_STANDARD 11)
set (CMAKE_EXE_LINKER_FLAGS -l sqlite3)

include_directories(client)
include_directories(client/inc)
include_directories(client/src)
include_directories(server)
include_directories(server/inc)
include_directories(server/src)

add_executable(uchat
        client/inc/header.h
        client/src/main.c
        server/inc/header.h
        server/src/main.c
        server/src/sqlite.c)
