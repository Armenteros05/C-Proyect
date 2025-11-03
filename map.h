#ifndef MAP_H
#define MAP_H

#include "vehicle.h"

extern char parkingMap[MAP_ROWS][MAP_COLS + 1];

void resetMap();
void printMap();

#endif
