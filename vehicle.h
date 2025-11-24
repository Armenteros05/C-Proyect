#ifndef VEHICLE_H
#define VEHICLE_H

#include "map.h"

typedef struct {
    int x;
    int y;
    char symbol;
    int parkedSpotIndex; // Índice de la plaza a la que se dirige o está aparcado (-1 si no tiene destino)
} Vehicle;

Vehicle createCar(int x, int y, char symbol);
void drawVehicle(Vehicle v);
void clearVehicle(Vehicle v);
// moveVehicle ahora retorna 1 si el coche se movió, 0 si ya llegó a su destino (la plaza)
int moveVehicle(Vehicle *v, int targetX, int targetY);

#endif