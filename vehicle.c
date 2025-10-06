#include <stdio.h>
#include "vehicle.h"

// General constructor
Vehicle createVehicle(int id, int x, int y, int width, int height, char symbol) {
    Vehicle v;
    v.id = id;
    v.x = x;
    v.y = y;
    v.width = width;
    v.height = height;
    v.symbol = symbol;
    return v;
}

// Small car 1x1
Vehicle createCarSmall(int id, int x, int y) {
    return createVehicle(id, x, y, 1, 1, 'S'); // 'S' for small car
}

// Large car 2x2
Vehicle createCarLarge(int id, int x, int y) {
    return createVehicle(id, x, y, 2, 2, 'L'); // 'L' for large car
}

// Move vehicle
void moveVehicle(Vehicle *v, int dx, int dy) {
    v->x += dx;
    v->y += dy;

    // Optional: boundary checks
    if (v->x < 0) v->x = 0;
    if (v->y < 0) v->y = 0;
    if (v->x + v->width > MAP_COLS) v->x = MAP_COLS - v->width;
    if (v->y + v->height > MAP_ROWS) v->y = MAP_ROWS - v->height;
}

// Draw vehicle into ASCII map
void drawVehicle(Vehicle v, char map[MAP_ROWS][MAP_COLS + 1]) {
    for (int i = 0; i < v.height; i++) {
        for (int j = 0; j < v.width; j++) {
            int row = v.y + i;
            int col = v.x + j;
            if (row >= 0 && row < MAP_ROWS && col >= 0 && col < MAP_COLS) {
                map[row][col] = v.symbol;
            }
        }
    }
}

// Print vehicle info
void printVehicle(Vehicle v) {
    printf("Vehicle %d at (%d,%d), size %dx%d, symbol '%c'\n",
           v.id, v.x, v.y, v.width, v.height, v.symbol);
}
