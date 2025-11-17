#ifndef VEHICLE_H
#define VEHICLE_H

#include "map.h"

typedef struct {
    int x;
    int y;
    char symbol;
} Vehicle;

Vehicle createCar(int x, int y, char symbol);
void drawVehicle(Vehicle v);
void clearVehicle(Vehicle v);
void moveVehicle(Vehicle *v, int newX, int newY);

#endif
