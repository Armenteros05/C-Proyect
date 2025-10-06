#include <stdio.h>
#include "vehicle.h"

Vehicle createVehicle(int id, int x, int y, int width, int height) {
    Vehicle v;
    v.id = id;
    v.x = x;
    v.y = y;
    v.width = width;
    v.height = height;
    return v;
}

void moveVehicle(Vehicle *v, int dx, int dy) {
    v->x += dx;
    v->y += dy;
}

void printVehicle(Vehicle v) {
    printf("Vehicle %d at position (%d, %d), size %dx%d\n",
           v.id, v.x, v.y, v.width, v.height);
}
