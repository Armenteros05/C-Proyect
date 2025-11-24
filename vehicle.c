#include "vehicle.h"
#include "map.h"
#include <math.h>

#define ENTRY_X 10
#define ENTRY_Y 2 // El pasillo superior principal

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

    // Limites de seguridad
    if (v.y >= 0 && v.y < MAP_ROWS && v.x > 0 && v.x < MAP_COLS - 1 && !isParked) {
        parkingMap[v.y][v.x - 1] = asciiMap[v.y][v.x - 1];
        parkingMap[v.y][v.x]     = asciiMap[v.y][v.x];
        parkingMap[v.y][v.x + 1] = asciiMap[v.y][v.x + 1];
    }
}

void drawVehicle(Vehicle v) {
    if (v.y >= 0 && v.y < MAP_ROWS && v.x > 0 && v.x < MAP_COLS - 1) {
        parkingMap[v.y][v.x - 1] = '[';
        parkingMap[v.y][v.x]     = v.symbol; // '='
        parkingMap[v.y][v.x + 1] = ']';
    }
}

int moveVehicle(Vehicle *v, int targetX, int targetY) {

    if (v->x == targetX && v->y == targetY) {
        drawVehicle(*v);
        return 0; // Llegó
    }

    clearVehicle(*v);
    int currentX = v->x;
    int currentY = v->y;
    int moved = 0;

    // --- Lógica para Mapa de Islas ---
    // El pasillo siempre está 2 filas por encima de la plaza en este diseño (o 3 para la fila 1)
    int aisleY;
    if (targetY == 5) aisleY = 2;      // Pasillo superior
    else if (targetY == 9) aisleY = 7; // Pasillo intermedio 1
    else aisleY = 11;                  // Pasillo intermedio 2 (para Y=13)

    // FASE 1: Ir verticalmente al pasillo correcto
    if (currentY != aisleY && currentX != targetX) {
        if (currentY < aisleY) v->y++;
        else v->y--;
        moved = 1;
    }
        // FASE 2: Moverse horizontalmente hasta el centro de la caja (X)
    else if (currentX != targetX) {
        if (currentX < targetX) v->x++;
        else v->x--;
        moved = 1;
    }
        // FASE 3: Bajar a la caja desde el pasillo
    else if (currentX == targetX && currentY != targetY) {
        v->y++; // Siempre es bajar en este diseño
        moved = 1;
    }

    drawVehicle(*v);
    return moved;
}