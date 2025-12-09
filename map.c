#include <string.h>
#include "map.h"

// LEYENDA:
// # = Muro
// . = Carretera (Gris)
// E = Zona Entrada
// X = Zona Salida
// G = Garita (Guard Booth)
// _ = Plaza

const char *asciiMap[MAP_ROWS] = {
        "#################################################################", // 0
        "# G           #...............................................#   #", // 1 (Garita Entrada)
        "#  EEEEEEE  #...............................................#   #", // 2
        "#. EEEEEEE .................................................#   #", // 3
        "#........... _______ ....... _______ ....... _______ .......#   #", // 4
        "#........... _______ ....... _______ ....... _______ .......#   #", // 5
        "#........... _______ ....... _______ ....... _______ .......#   #", // 6
        "#...........................................................#   #", // 7
        "#........... _______ ....... _______ ....... _______ .......#...#", // 8
        "#........... _______ ....... _______ ....... _______ .......#...#", // 9
        "#........... _______ ....... _______ ....... _______ .......#...#", // 10
        "#...........................................................#...#", // 11
        "#........... _______ ....... _______ ....... _______ .......#...#", // 12
        "#........... _______ ....... _______ ....... _______ .......#...#", // 13
        "#........... _______ ....... _______ ....... _______ .......#...#", // 14
        "#...........................................................#...#", // 15
        "#........... _______ ....... _______ ....... _______ .......#...#", // 16
        "#........... _______ ....... _______ ....... _______ .......#...#", // 17
        "#........... _______ ....... _______ ....... _______ .......#...#", // 18
        "#...........................................................#...#", // 19
        "#........... _______ ....... _______ ....... _______ .......#...#", // 20
        "#........... _______ ....... _______ ....... _______ .......#...#", // 21
        "#........... _______ ....... _______ ....... _______ .......#...#", // 22
        "####################################################### G ..... #", // 23 (Garita Salida)
        "                                                       XXXXXX    "  // 24 (Salida física)
};

char parkingMap[MAP_ROWS][MAP_COLS + 1];

// Coordenadas de las plazas (Sin cambios salvo quitar duplicados)
ParkingSpot spots[NUM_SPOTS] = {
        { 16, 5, 0 }, { 16, 9, 0 }, { 16, 13, 0 }, { 16, 17, 0 }, { 16, 21, 0 },
        { 32, 5, 0 }, { 32, 9, 0 }, { 32, 13, 0 }, { 32, 17, 0 }, { 32, 21, 0 },
        { 48, 5, 0 }, { 48, 9, 0 }, { 48, 13, 0 }, { 48, 17, 0 }, { 48, 21, 0 }
};

void resetMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        if (i < 24) strncpy(parkingMap[i], asciiMap[i], MAP_COLS);
        parkingMap[i][MAP_COLS] = '\0';
    }
    for (int i = 0; i < NUM_SPOTS; i++) {
        spots[i].isOccupied = 0;
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

// Neue Funktion: Reserviert einen Platz (vor dem Parken)
void reserveSpot(int spotIndex) {
    if (spotIndex >= 0 && spotIndex < NUM_SPOTS) {
        if (spots[spotIndex].isOccupied == 0) {
            spots[spotIndex].isOccupied = 2; // 2 = reserviert
        }
    }
}

// Falls eine Reservation zurückgenommen werden muss
void releaseSpotReservation(int spotIndex) {
    if (spotIndex >= 0 && spotIndex < NUM_SPOTS) {
        if (spots[spotIndex].isOccupied == 2) {
            spots[spotIndex].isOccupied = 0;
        }
    }
}
