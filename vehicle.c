#include "vehicle.h"
#include <math.h> // Si usas abs()

// Ubicación de las carreteras verticales en el mapa
#define ROAD_1_X 14
#define ROAD_2_X 34

Vehicle createCar(int x, int y, char symbol) {
    Vehicle v = { x, y, symbol, -1 };
    return v;
}

int moveVehicle(Vehicle *v, int targetX, int targetY) {
    // Si ya llegó, no se mueve
    if (v->x == targetX && v->y == targetY) {
        return 0;
    }

    int currentX = v->x;
    int currentY = v->y;
    int moved = 0;

    // 1. DECIDIR QUÉ CARRETERA TOMAR
    // Si la plaza está en la columna 1 (X=4) o 2 (X=24), usa ROAD 1.
    // Si está en la columna 3 (X=44), usa ROAD 2.
    int targetRoadX = (targetX <= 24) ? ROAD_1_X : ROAD_2_X;

    // FASE 1: Navegar horizontalmente hacia la carretera vertical correcta (desde la entrada)
    if (currentY <= 2 && currentX != targetRoadX) {
        if (currentX < targetRoadX) v->x++;
        else v->x--;
        moved = 1;
    }
        // FASE 2: Bajar por la carretera vertical hasta la fila correcta
    else if (currentX == targetRoadX && currentY != targetY) {
        if (currentY < targetY) v->y++;
        else v->y--;
        moved = 1;
    }
        // FASE 3: Salir de la carretera y entrar en la plaza
    else if (currentY == targetY && currentX != targetX) {
        if (currentX < targetX) v->x++;
        else v->x--;
        moved = 1;

        // "Frenada": Evitar que se pase de la coordenada si va muy rápido o por error
        if ((currentX < targetX && v->x > targetX) || (currentX > targetX && v->x < targetX)) {
            v->x = targetX;
        }
    }
        // Fallback: Si se pierde, intenta ir directo
    else if (moved == 0) {
        if (currentX < targetX) v->x++;
        else if (currentX > targetX) v->x--;
        else if (currentY < targetY) v->y++;
        else v->y--;
        moved = 1;
    }

    return moved;
}