#include <stdio.h>
#include <string.h>
#include "map.h"

// DISEÑO: PARKING | CTEA | PARKING | CTEA | PARKING
// Las plazas son cajas de 7 de ancho: "+-----+"
// Las carreteras son de 5 de ancho:   "| . |"
const char *asciiMap[MAP_ROWS] = {
        "+=============================================================+", // 0
        "| ENTER -> .................................................  |", // 1
        "| ..........................................................  |", // 2
        "+-------+   | . |   +-------+   | . |   +-------+",              // 3
        "|       |   | . |   |       |   | . |   |       |",              // 4 (Y=4)
        "+-------+   | . |   +-------+   | . |   +-------+",              // 5
        "            | . |               | . |            ",              // 6
        "+-------+   | . |   +-------+   | . |   +-------+",              // 7
        "|       |   | . |   |       |   | . |   |       |",              // 8 (Y=8)
        "+-------+   | . |   +-------+   | . |   +-------+",              // 9
        "            | . |               | . |            ",              // 10
        "+-------+   | . |   +-------+   | . |   +-------+",              // 11
        "|       |   | . |   |       |   | . |   |       |",              // 12 (Y=12)
        "+-------+   | . |   +-------+   | . |   +-------+",              // 13
        "            | . |               | . |            ",              // 14
        "+-------+   | . |   +-------+   | . |   +-------+",              // 15
        "|       |   | . |   |       |   | . |   |       |",              // 16 (Y=16)
        "+-------+   | . |   +-------+   | . |   +-------+",              // 17
        "            | . |               | . |            ",              // 18
        "+-------+   | . |   +-------+   | . |   +-------+",              // 19
        "|       |   | . |   |       |   | . |   |       |",              // 20 (Y=20)
        "+-------+   | . |   +-------+   | . |   +-------+",              // 21
        "|                                             |               |", // 22
        "+-------------------------------------------------------------+"  // 23
};

char parkingMap[MAP_ROWS][MAP_COLS + 1];

// COORDENADAS X (Centros):
// Columna P1: X=4  (Caja de 0 a 8)
// Columna P2: X=24 (Caja de 20 a 28)
// Columna P3: X=44 (Caja de 40 a 48)
// Carretera 1: X=14 | Carretera 2: X=34
ParkingSpot spots[NUM_SPOTS] = {
        // --- COLUMNA 1 (Izquierda) ---
        { 4, 4, 0, 0, 8, 3, 5 }, { 4, 8, 0, 0, 8, 7, 9 }, { 4, 12, 0, 0, 8, 11, 13 },
        { 4, 16, 0, 0, 8, 15, 17 }, { 4, 20, 0, 0, 8, 19, 21 }, { 4, 20, 0, 0, 8, 19, 21 }, // Extra buffer

        // --- COLUMNA 2 (Centro) ---
        { 24, 4, 0, 20, 28, 3, 5 }, { 24, 8, 0, 20, 28, 7, 9 }, { 24, 12, 0, 20, 28, 11, 13 },
        { 24, 16, 0, 20, 28, 15, 17 }, { 24, 20, 0, 20, 28, 19, 21 }, { 24, 20, 0, 20, 28, 19, 21 },

        // --- COLUMNA 3 (Derecha) ---
        { 44, 4, 0, 40, 48, 3, 5 }, { 44, 8, 0, 40, 48, 7, 9 }, { 44, 12, 0, 40, 48, 11, 13 },
        { 44, 16, 0, 40, 48, 15, 17 }, { 44, 20, 0, 40, 48, 19, 21 }, { 44, 20, 0, 40, 48, 19, 21 }
};

void resetMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        strncpy(parkingMap[i], asciiMap[i], MAP_COLS);
        parkingMap[i][MAP_COLS] = '\0';
    }
    for (int i = 0; i < NUM_SPOTS; i++) {
        spots[i].isOccupied = 0;
    }
}

// Función auxiliar para saber si una coordenada (x,y) pertenece visualmente a una plaza
int getSpotIndexAt(int x, int y) {
    for (int i = 0; i < NUM_SPOTS; i++) {
        // Chequeamos si x,y está dentro de la caja visual de la plaza
        if (x >= spots[i].x_min && x <= spots[i].x_max &&
            y >= spots[i].y_min && y <= spots[i].y_max) {
            return i;
        }
    }
    return -1;
}

// AQUÍ APLICAMOS EL COLOR
void printMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {

            // Verificamos si este pixel es parte de una plaza
            int spotIdx = getSpotIndexAt(j, i);

            if (spotIdx != -1) {
                // Si es una plaza, decidimos el color
                if (spots[spotIdx].isOccupied) {
                    printf("%s%c%s", ANSI_COLOR_RED, parkingMap[i][j], ANSI_COLOR_RESET);
                } else {
                    // Si está libre, VERDE
                    printf("%s%c%s", ANSI_COLOR_GREEN, parkingMap[i][j], ANSI_COLOR_RESET);
                }
            } else {
                // Si no es plaza (carretera, muro ext), color normal
                printf("%c", parkingMap[i][j]);
            }
        }
        printf("\n");
    }
}

int findFreeSpot() {
    for (int i = 0; i < NUM_SPOTS; i++) {
        if (spots[i].isOccupied == 0) return i;
    }
    return -1;
}

void occupySpot(int spotIndex) {
    if (spotIndex >= 0 && spotIndex < NUM_SPOTS) {
        spots[spotIndex].isOccupied = 1;
    }
}