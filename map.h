#ifndef MAP_H
#define MAP_H

#define MAP_ROWS 18
#define MAP_COLS 70
#define NUM_SPOTS 15 // 15 Plazas "Isla"

typedef struct {
    int x;
    int y;
    int isOccupied;
} ParkingSpot;

extern char parkingMap[MAP_ROWS][MAP_COLS + 1];
extern const char *asciiMap[MAP_ROWS];
extern ParkingSpot spots[NUM_SPOTS];

void resetMap();
void printMap();
int findFreeSpot();
void occupySpot(int spotIndex);

#endif