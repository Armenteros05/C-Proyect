#include <stdio.h>
#include <string.h>
#include "map.h"

// NUEVO MAPA "ISLAS" - Separación visual total
const char *asciiMap[MAP_ROWS] = {
        "+====================================================================+", // 0
        "| ENTER -> .......................................................   |", // 1 (Pasillo Entrada)
        "| ................................................................   |", // 2 (Pasillo Principal Superior)
        "+====================================================================+", // 3
        "    +-------+   +-------+   +-------+   +-------+   +-------+",           // 4 (Techos Fila 1)
        "    |       |   |       |   |       |   |       |   |       |",           // 5 (PLAZAS Y=5)
        "    +-------+   +-------+   +-------+   +-------+   +-------+",           // 6
        "......................................................................", // 7 (Pasillo Intermedio 1)
        "    +-------+   +-------+   +-------+   +-------+   +-------+",           // 8
        "    |       |   |       |   |       |   |       |   |       |",           // 9 (PLAZAS Y=9)
        "    +-------+   +-------+   +-------+   +-------+   +-------+",           // 10
        "......................................................................", // 11 (Pasillo Intermedio 2)
        "    +-------+   +-------+   +-------+   +-------+   +-------+",           // 12
        "    |       |   |       |   |       |   |       |   |       |",           // 13 (PLAZAS Y=13)
        "    +-------+   +-------+   +-------+   +-------+   +-------+",           // 14
        "+====================================================================+", // 15
        "|   ......................................................... EXIT ->|", // 16 (Pasillo Salida)
        "+====================================================================+"  // 17
};

char parkingMap[MAP_ROWS][MAP_COLS + 1];

// CALCULO DE COORDENADAS CENTRADAS
// Cada caja interna tiene 7 espacios: "| 1 2 3(C)4 5 6 7 |"
// El centro exacto donde irá el '=' del coche '[=]' es el 4º espacio.
// Centros X calculados: 8, 20, 32, 44, 56
ParkingSpot spots[NUM_SPOTS] = {
        // --- Fila 1 (Y=5) ---
        { 8, 5, 0 }, { 20, 5, 0 }, { 32, 5, 0 }, { 44, 5, 0 }, { 56, 5, 0 },

        // --- Fila 2 (Y=9) ---
        { 8, 9, 0 }, { 20, 9, 0 }, { 32, 9, 0 }, { 44, 9, 0 }, { 56, 9, 0 },

        // --- Fila 3 (Y=13) ---
        { 8, 13, 0 }, { 20, 13, 0 }, { 32, 13, 0 }, { 44, 13, 0 }, { 56, 13, 0 }
};

void resetMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        strncpy(parkingMap[i], asciiMap[i], MAP_COLS);
        parkingMap[i][MAP_COLS] = '\0';
    }
    // Reiniciar lógica de ocupación
    for (int i = 0; i < NUM_SPOTS; i++) {
        spots[i].isOccupied = 0;
    }
}

void printMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        printf("%s\n", parkingMap[i]);
    }
}

int findFreeSpot() {
    for (int i = 0; i < NUM_SPOTS; i++) {
        if (spots[i].isOccupied == 0) {
            return i;
        }
    }
    return -1;
}

void occupySpot(int spotIndex) {
    if (spotIndex >= 0 && spotIndex < NUM_SPOTS) {
        spots[spotIndex].isOccupied = 1;
    }
}