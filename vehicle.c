#include "vehicle.h"
#include <math.h>

// Coordenadas EXACTAS de los carriles verticales (Centrados en los puntos)
#define ROAD_1_X 6   // Carril izquierdo
#define ROAD_2_X 24  // Carril central
#define ROAD_3_X 40  // Carril derecho

Vehicle createCar(int x, int y, char symbol) {
    Vehicle v = { x, y, symbol, -1 };
    return v;
}

int moveVehicle(Vehicle *v, int targetX, int targetY) {
    // Si ya llegó, stop
    if (v->x == targetX && v->y == targetY) return 0;

    int cx = v->x;
    int cy = v->y;
    int moved = 0;

    // 1. ELEGIR RUTA
    // Si la plaza está en X=16, usa ROAD 1 (X=6)
    // Si la plaza está en X=32, usa ROAD 2 (X=24)
    // Si la plaza está en X=48, usa ROAD 3 (X=40)
    int roadX = ROAD_1_X;
    if (targetX >= 30) roadX = ROAD_2_X;
    if (targetX >= 45) roadX = ROAD_3_X;

    // LÓGICA DE MOVIMIENTO "ESCUADRA" (Sin diagonales raras)

    // FASE A: Estamos arriba (zona entrada), ir lateralmente hasta pillar la columna
    if (cy < 4 && cx != roadX) {
        if (cx < roadX) v->x++; else v->x--;
        moved = 1;
    }
        // FASE B: Bajar por la columna (carretera) hasta la altura de la plaza
    else if (cx == roadX && cy != targetY) {
        if (cy < targetY) v->y++; else v->y--;
        moved = 1;
    }
        // FASE C: Entrar lateralmente a la plaza
    else if (cy == targetY && cx != targetX) {
        if (cx < targetX) v->x++; else v->x--;
        moved = 1;
    }
        // FASE D (Emergencia): Si el coche se pierde, intenta ir directo
    else if (!moved) {
        if (cx < targetX) v->x++; else if (cx > targetX) v->x--;
        else if (cy < targetY) v->y++; else v->y--;
        moved = 1;
    }

    return moved;
}