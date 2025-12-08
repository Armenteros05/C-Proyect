#include "vehicle.h"
#include <math.h>

#define ROAD_1_X 6
#define ROAD_2_X 24
#define ROAD_3_X 40

Vehicle createCar(int x, int y, char symbol) {
    Vehicle v;
    v.x = (float)x; // Convertimos a float
    v.y = (float)y;
    v.symbol = symbol;
    v.parkedSpotIndex = -1;
    return v;
}

// Función auxiliar para acercarse suavemente
float approach(float current, float target, float speed) {
    if (fabs(current - target) < speed) return target; // Si está muy cerca, encaja
    if (current < target) return current + speed;
    if (current > target) return current - speed;
    return current;
}

int moveVehicle(Vehicle *v, int targetX, int targetY, float speed) {
    // Si ya llegó (con un margen de error pequeño), retornamos 0
    if (fabs(v->x - targetX) < 0.1 && fabs(v->y - targetY) < 0.1) {
        v->x = targetX; // Asegurar posición exacta al llegar
        v->y = targetY;
        return 0;
    }

    float cx = v->x;
    float cy = v->y;

    // Determinar qué carretera usar
    int roadX = ROAD_1_X;
    if (targetX >= 30) roadX = ROAD_2_X;
    if (targetX >= 45) roadX = ROAD_3_X;

    // LÓGICA DE MOVIMIENTO SUAVE
    // Prioridades:
    // 1. Si estamos en la zona superior (Y < 4) y no en la columna correcta -> Mover X
    // 2. Si estamos en la columna correcta pero no en la altura correcta -> Mover Y
    // 3. Si estamos en la altura correcta -> Mover X hacia la plaza

    // FASE A: Navegación horizontal inicial (Zona superior)
    if (cy < 4 && fabs(cx - roadX) > 0.1) {
        v->x = approach(cx, roadX, speed);
    }
        // FASE B: Navegación vertical (Bajar por la carretera)
    else if (fabs(cx - roadX) <= 0.1 && fabs(cy - targetY) > 0.1) {
        v->x = roadX; // Mantenerse pegado al carril
        v->y = approach(cy, targetY, speed);
    }
        // FASE C: Entrar a la plaza
    else {
        v->y = targetY; // Mantener altura
        v->x = approach(cx, targetX, speed);
    }

    return 1; // Sigue moviéndose
}