#include "vehicle.h"
#include <math.h>
#include "colors.h"


#define ROAD_1_X 6
#define ROAD_2_X 24
#define ROAD_3_X 40

Vehicle createCar(int x, int y, char symbol) {
    Vehicle v;
    v.x = (float)x;
    v.y = (float)y;
    v.symbol = symbol;
    v.parkedSpotIndex = -1;
    return v;
}

// Función auxiliar para acercarse suavemente
float approach(float current, float target, float speed) {
    if (fabs(current - target) < speed) return target;
    if (current < target) return current + speed;
    if (current > target) return current - speed;
    return current;
}

int moveVehicle(Vehicle *v, int targetX, int targetY, float speed) {
    // Si ya llegó
    if (fabs(v->x - targetX) < 0.1 && fabs(v->y - targetY) < 0.1) {
        v->x = (float)targetX;
        v->y = (float)targetY;
        return 0;
    }

    float cx = v->x;
    float cy = v->y;

    // --- LÓGICA DE SALIDA (Si vamos hacia la salida abajo a la derecha) ---
    if (targetY > 20 && targetX > 50) {
        // 1. Salir de la plaza hacia el carril vertical más cercano
        // Identificar carril más cercano
        int nearestRoad = ROAD_1_X;
        if (cx > 20) nearestRoad = ROAD_2_X;
        if (cx > 36) nearestRoad = ROAD_3_X;

        // FASE 1: Ir horizontalmente al carril vertical (Si no estamos ya abajo)
        if (cy < 22 && fabs(cx - nearestRoad) > 0.5) {
            v->x = approach(cx, nearestRoad, speed);
        }
            // FASE 2: Bajar por el carril hasta el fondo (Pasillo inferior Y=22)
        else if (fabs(cx - nearestRoad) <= 0.5 && cy < 22) {
            v->x = nearestRoad;
            v->y = approach(cy, 22, speed); // Bajar hasta el pasillo inferior
        }
            // FASE 3: Ir a la derecha por el pasillo inferior hacia la salida
        else if (cy >= 22 && cx < targetX) {
            v->y = 22; // Mantenerse en el pasillo inferior
            v->x = approach(cx, targetX, speed);
        }
            // FASE 4: Una vez en la X correcta, bajar por la salida
        else if (fabs(cx - targetX) < 1.0) {
            v->x = targetX;
            v->y = approach(cy, targetY, speed);
        }
        return 1;
    }

    // --- LÓGICA DE ENTRADA (Estándar) ---
    int roadX = ROAD_1_X;
    if (targetX >= 30) roadX = ROAD_2_X;
    if (targetX >= 45) roadX = ROAD_3_X;

    if (cy < 4 && fabs(cx - roadX) > 0.1) {
        v->x = approach(cx, roadX, speed);
    }
    else if (fabs(cx - roadX) <= 0.1 && fabs(cy - targetY) > 0.1) {
        v->x = roadX;
        v->y = approach(cy, targetY, speed);
    }
    else {
        v->y = targetY;
        v->x = approach(cx, targetX, speed);
    }

    return 1;
}