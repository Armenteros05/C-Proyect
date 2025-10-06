#ifndef VEHICLE_H
#define VEHICLE_H

#define MAP_ROWS 30
#define MAP_COLS 80

typedef struct {
    int id;         // Vehicle identifier
    int x, y;       // Top-left coordinates in the map
    int width;      // Vehicle width in characters
    int height;     // Vehicle height in characters
    char symbol;    // Character used to draw the vehicle
} Vehicle;

// Functions
Vehicle createVehicle(int id, int x, int y, int width, int height, char symbol);
Vehicle createCarSmall(int id, int x, int y); // 1x1
Vehicle createCarLarge(int id, int x, int y); // 2x2

void moveVehicle(Vehicle *v, int dx, int dy);
void drawVehicle(Vehicle v, char map[MAP_ROWS][MAP_COLS + 1]);
void printVehicle(Vehicle v);

#endif
