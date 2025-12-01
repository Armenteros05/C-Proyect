cmake_minimum_required(VERSION 3.26)
project(C_Project C)

set(CMAKE_C_STANDARD 11)

# --- TU RUTA EXACTA (YA CORREGIDA) ---
set(SDL2_PATH "C:/Users/Sergio/Desktop/UAX/C-Proyect/SDL2/x86_64-w64-mingw32")

# Le decimos a CLion dónde están las cosas
include_directories(${SDL2_PATH}/include)
link_directories(${SDL2_PATH}/lib)

# Tus archivos
add_executable(C_Project
        main.c
        map.c
        map.h
        vehicle.c
        vehicle.h
        graphics.c
        graphics.h
)

# Enlazar librerías
target_link_libraries(C_Project mingw32 SDL2main SDL2)

# Truco para copiar la DLL automáticamente
if (WIN32)
    add_custom_command(TARGET C_Project POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_PATH}/bin/SDL2.dll"
            $<TARGET_FILE_DIR:C_Project>)
endif()