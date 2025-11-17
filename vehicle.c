#include <stdio.h>
#include "vehicle.h"
#include "map.h"

Vehicle createCarSmall(int x, int y) {
    Vehicle v = {x, y, SMALL, 'S'};
    return v;
}

Vehicle createCarLarge(int x, int y) {
    Vehicle v = {x, y, LARGE, 'L'};
    return v;
}

void drawVehicle(Vehicle v) {
    if (v.x >= 0 && v.x < MAP_COLS && v.y >= 0 && v.y < MAP_ROWS) {
        parkingMap[v.y][v.x] = v.symbol;
    }
}
