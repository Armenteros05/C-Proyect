#ifndef VEHICLE_H
#define VEHICLE_H

#include "map.h"

typedef struct {
    float x; // AHORA ES FLOAT PARA MOVIMIENTO SUAVE
    float y;
    char symbol;
    int parkedSpotIndex;
} Vehicle;

Vehicle createCar(int x, int y, char symbol);
// Añadimos parámetro de velocidad
int moveVehicle(Vehicle *v, int targetX, int targetY, float speed);
void drawVehicle(Vehicle v);


#endif