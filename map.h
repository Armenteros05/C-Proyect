#ifndef MAP_H
#define MAP_H

#define MAP_ROWS 24
#define MAP_COLS 65
#define NUM_SPOTS 15  // changed from 18 to 15


typedef struct {
    int x;
    int y;
    int isOccupied;
} ParkingSpot;

// Definimos el mapa como caracteres para la lógica, aunque luego dibujemos gráficos
extern char parkingMap[MAP_ROWS][MAP_COLS + 1];
extern const char *asciiMap[MAP_ROWS];
extern ParkingSpot spots[NUM_SPOTS];

void resetMap();
int findFreeSpot();
void occupySpot(int spotIndex);
void reserveSpot(int spotIndex);
void releaseSpotReservation(int spotIndex);
void initMap();
void printMap();


#endif