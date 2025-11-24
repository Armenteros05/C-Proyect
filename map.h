#ifndef MAP_H
#define MAP_H

#define MAP_ROWS 22
#define MAP_COLS 85
#define NUM_SPOTS 20 // Hay 20 plazas de aparcamiento identificadas en el mapa.

// Estructura para gestionar las plazas de aparcamiento
typedef struct {
    int x;
    int y;
    int isOccupied; // 0: Libre, 1: Ocupada
} ParkingSpot;

extern char parkingMap[MAP_ROWS][MAP_COLS + 1];
extern const char *asciiMap[MAP_ROWS];
extern ParkingSpot spots[NUM_SPOTS]; // Array de todas las plazas

void resetMap();
void printMap();

// Funciones de gestión de plazas
int findFreeSpot();
void occupySpot(int spotIndex);

#endif