#include "vehicle.h"
#include "map.h"
#include <math.h>

#define ENTRY_X 10
#define ENTRY_Y 1

Vehicle createCar(int x, int y, char symbol) {
    Vehicle v = { x, y, symbol, -1 };
    return v;
}

void clearVehicle(Vehicle v) {
    int isParked = 0;
    // Solo si ha llegado a la coordenada exacta de destino, lo consideramos aparcado.
    if (v.parkedSpotIndex != -1) {
        if (v.x == spots[v.parkedSpotIndex].x && v.y == spots[v.parkedSpotIndex].y) {
            isParked = 1;
        }
    }

    if (v.y >= 0 && v.y < MAP_ROWS && v.x >= 0 && v.x < MAP_COLS && !isParked) {
        // Restaurar el carácter original del mapa
        parkingMap[v.y][v.x] = asciiMap[v.y][v.x];
    }
}

void drawVehicle(Vehicle v) {
    if (v.y >= 0 && v.y < MAP_ROWS && v.x >= 0 && v.x < MAP_COLS) {
        parkingMap[v.y][v.x] = v.symbol;
    }
}

// Mueve el vehículo usando un Waypoint Dinámico.
int moveVehicle(Vehicle *v, int targetX, int targetY) {

    if (v->x == targetX && v->y == targetY) {
        drawVehicle(*v);
        return 0; // Ya llegó
    }

    clearVehicle(*v);
    int currentX = v->x;
    int currentY = v->y;
    int moved = 0;

    // Determinar el Pasillo/Waypoint Y (El pasillo de circulación más cercano)
    int waypointY;
    if (targetY <= 5) { // Fila 1 (Y=4) -> Pasillo en Y=6
        waypointY = 6;
    } else if (targetY <= 8) { // Fila 2 (Y=7) -> Pasillo en Y=9
        waypointY = 9;
    } else if (targetY <= 11) { // Fila 3 (Y=10) -> Pasillo en Y=12
        waypointY = 12;
    } else { // Fila 4 (Y=13) -> Pasillo en Y=15
        waypointY = 15;
    }

    // FASE 1: Moverse Verticalmente al Pasillo (waypointY)
    // El coche se mueve verticalmente solo si no está en la X final.
    if (currentY != waypointY && currentX != targetX) {
        if (currentY < waypointY) {
            v->y++;
            moved = 1;
        } else if (currentY > waypointY) {
            v->y--;
            moved = 1;
        }
    }

    // FASE 2: Moverse Horizontalmente (X) a la columna de la plaza
    // Se ejecuta si no se movió en FASE 1 O si ya está en el pasillo correcto (waypointY).
    if (moved == 0 && currentX != targetX) {
        if (currentX < targetX) {
            v->x++;
        } else {
            v->x--;
        }
        moved = 1;
    }

    // FASE 3: Moverse Verticalmente (Y) hacia el punto final de aparcamiento
    // Se ejecuta solo si ya está en la X correcta.
    if (moved == 0 && currentX == targetX && currentY != targetY) {
        if (currentY > targetY) {
            v->y--; // Subir hacia la posición de aparcamiento (Y más pequeña)
        } else {
            v->y++; // Bajar (sólo para la fila 4, pero es el movimiento correcto)
        }
        moved = 1;
    }

    drawVehicle(*v);
    return moved;
}