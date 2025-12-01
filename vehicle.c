#include "vehicle.h"
#include "map.h"
#include <math.h>

#define ENTRY_Y 1
// Definimos las coordenadas X de las carreteras verticales
#define ROAD_1_X 14
#define ROAD_2_X 34

Vehicle createCar(int x, int y, char symbol) {
    Vehicle v = { x, y, symbol, -1 };
    return v;
}

void clearVehicle(Vehicle v) {
    int isParked = 0;
    if (v.parkedSpotIndex != -1) {
        if (v.x == spots[v.parkedSpotIndex].x && v.y == spots[v.parkedSpotIndex].y) {
            isParked = 1;
        }
    }
    if (v.y >= 0 && v.y < MAP_ROWS && v.x > 0 && v.x < MAP_COLS - 1 && !isParked) {
        parkingMap[v.y][v.x - 1] = asciiMap[v.y][v.x - 1];
        parkingMap[v.y][v.x]     = asciiMap[v.y][v.x];
        parkingMap[v.y][v.x + 1] = asciiMap[v.y][v.x + 1];
    }
}

void drawVehicle(Vehicle v) {
    if (v.y >= 0 && v.y < MAP_ROWS && v.x > 0 && v.x < MAP_COLS - 1) {
        parkingMap[v.y][v.x - 1] = '[';
        parkingMap[v.y][v.x]     = v.symbol;
        parkingMap[v.y][v.x + 1] = ']';
    }
}

int moveVehicle(Vehicle *v, int targetX, int targetY) {

    if (v->x == targetX && v->y == targetY) {
        drawVehicle(*v);
        return 0;
    }

    clearVehicle(*v);
    int currentX = v->x;
    int currentY = v->y;
    int moved = 0;

    // --- LÓGICA DE DOBLE CARRETERA ---

    // 1. Elegir qué carretera tomar
    // Si la meta está en X=4 (Col 1) o X=24 (Col 2), usar ROAD 1.
    // Si la meta está en X=44 (Col 3), usar ROAD 2.
    int targetRoadX = (targetX <= 24) ? ROAD_1_X : ROAD_2_X;

    // FASE 1: Ir a la carretera vertical adecuada desde la entrada
    if (currentY <= 2 && currentX != targetRoadX) {
        if (currentX < targetRoadX) v->x++;
        else v->x--;
        moved = 1;
    }
        // FASE 2: Bajar por la carretera hasta la fila Y correcta
    else if (currentX == targetRoadX && currentY != targetY) {
        if (currentY < targetY) v->y++;
        else v->y--;
        moved = 1;
    }
        // FASE 3: Salir de la carretera hacia la plaza
    else if (currentY == targetY && currentX != targetX) {
        if (currentX < targetX) v->x++;
        else v->x--;
        moved = 1;

        // Anti-overshoot
        if ((currentX < targetX && v->x > targetX) || (currentX > targetX && v->x < targetX)) {
            v->x = targetX;
        }
    }
        // Fallback
    else if (moved == 0) {
        if (currentX < targetX) v->x++;
        else if (currentX > targetX) v->x--;
        else if (currentY < targetY) v->y++;
        else v->y--;
        moved = 1;
    }

    drawVehicle(*v);
    return moved;
}