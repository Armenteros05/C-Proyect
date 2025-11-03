cmake_minimum_required(VERSION 3.26)
project(C_Proyect C)

set(CMAKE_C_STANDARD 11)

add_executable(main
        main.c
        map.c
        vehicle.c
)

add_executable(map_viewer
        map_viewer.c
        map.c
)
