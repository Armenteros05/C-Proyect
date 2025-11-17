#ifndef MAP_H
#define MAP_H

#define MAP_ROWS 22
#define MAP_COLS 85

extern char parkingMap[MAP_ROWS][MAP_COLS + 1];
extern const char *asciiMap[MAP_ROWS];

void resetMap();
void printMap();

#endif
