#include "vehicle.h"
#include "map.h"

Vehicle createCar(int x, int y, char symbol) {
    Vehicle v = { x, y, symbol };
    return v;
}

void clearVehicle(Vehicle v) {
    if (v.y >= 0 && v.y < MAP_ROWS && v.x >= 0 && v.x < MAP_COLS) {
        parkingMap[v.y][v.x] = asciiMap[v.y][v.x]; // restore original character
    }
}

void drawVehicle(Vehicle v) {
    if (v.y >= 0 && v.y < MAP_ROWS && v.x >= 0 && v.x < MAP_COLS) {
        parkingMap[v.y][v.x] = v.symbol;
    }
}

void moveVehicle(Vehicle *v, int newX, int newY) {
    clearVehicle(*v);
    v->x = newX;
    v->y = newY;
    drawVehicle(*v);
}
