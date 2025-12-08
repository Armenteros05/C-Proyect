cmake_minimum_required(VERSION 3.10)
project(ParkingSimulator C)

set(CMAKE_C_STANDARD 99)

# =========================================================
#  CONFIGURACIÓN DE LA RUTA GENÉRICA (PORTABLE)
# =========================================================
# ${CMAKE_CURRENT_SOURCE_DIR} es la clave.
# Significa: "La carpeta donde se ha descargado este proyecto"

# 1. Dónde buscar los archivos .h (headers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SDL2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 2. Dónde buscar los archivos .a (librerías)
link_directories(${CMAKE_CURRENT_SOURCE_DIR})

# =========================================================
#  ARCHIVOS DEL PROYECTO
# =========================================================
set(SOURCE_FILES
        main.c
        graphics.c
        graphics.h
        map.c
        map.h
        vehicle.c
        vehicle.h
)

add_executable(parking ${SOURCE_FILES})

# =========================================================
#  VINCULACIÓN DE LIBRERÍAS (LINKING)
# =========================================================
# Aquí unimos tu código con las librerías que están EN LA CARPETA.
target_link_libraries(parking
        mingw32
        ${CMAKE_CURRENT_SOURCE_DIR}/libSDL2main.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libSDL2.a
        # Dependencias de Windows obligatorias (vienen preinstaladas en Windows)
        ole32
        oleaut32
        imm32
        winmm
        version
        setupapi
        gdi32
        user32
)

# =========================================================
#  AUTO-COPIA DE RECURSOS (Imágenes y DLL)
# =========================================================
# Esto copia la DLL y las imágenes a la carpeta de "debug" automáticamente
# para que al darle al Play no dé error de "falta archivo".
file(GLOB BMP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.bmp")
file(COPY ${BMP_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/SDL2.dll" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})