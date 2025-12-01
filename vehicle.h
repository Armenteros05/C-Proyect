#ifndef VEHICLE_H
#define VEHICLE_H

#include "map.h"

typedef struct {
    int x;
    int y;
    char symbol; // Para lógica interna
    int parkedSpotIndex; // -1 si no tiene plaza o no ha llegado
} Vehicle;

Vehicle createCar(int x, int y, char symbol);
// Nota: Las funciones drawVehicle/clearVehicle se simplifican porque SDL dibuja todo de nuevo cada frame
int moveVehicle(Vehicle *v, int targetX, int targetY);

#endif