#include <stdio.h>
#include <string.h>
#include "map.h"

// Original ASCII map
const char *asciiMap[MAP_ROWS] = {
        "+---------------------------------------------------------------------------------+",
        "| ENTER                                                                           |",
        "| HERE                                                                            |",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|", // Y=4: Posición de aparcamiento Fila 1
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|", // Y=7: Posición de aparcamiento Fila 2
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|", // Y=10: Posición de aparcamiento Fila 3
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|", // Y=13: Posición de aparcamiento Fila 4
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|                                                                            EXIT |",
        "|                                                                            HERE |",
        "|---------------------------------------------------------------------------------|"
};

char parkingMap[MAP_ROWS][MAP_COLS + 1];

// Coordenadas definitivas de las 20 plazas (pegadas al borde Y)
ParkingSpot spots[NUM_SPOTS] = {
        // Fila 1 (Y=4)
        { 10, 4, 0 }, { 28, 4, 0 }, { 46, 4, 0 }, { 64, 4, 0 }, { 80, 4, 0 },
        // Fila 2 (Y=7)
        { 10, 7, 0 }, { 28, 7, 0 }, { 46, 7, 0 }, { 64, 7, 0 }, { 80, 7, 0 },
        // Fila 3 (Y=10)
        { 10, 10, 0 }, { 28, 10, 0 }, { 46, 10, 0 }, { 64, 10, 0 }, { 80, 10, 0 },
        // Fila 4 (Y=13)
        { 10, 13, 0 }, { 28, 13, 0 }, { 46, 13, 0 }, { 64, 13, 0 }, { 80, 13, 0 },
};

void resetMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        strncpy(parkingMap[i], asciiMap[i], MAP_COLS);
        parkingMap[i][MAP_COLS] = '\0';
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