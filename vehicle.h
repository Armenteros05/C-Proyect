#ifndef VEHICLE_H
#define VEHICLE_H

// Vehicle "class" definition
typedef struct {
    int id;       // Vehicle identifier
    int x, y;     // Coordinates
    int width;    // Vehicle width
    int height;   // Vehicle height
} Vehicle;

// Functions (methods)
Vehicle createVehicle(int id, int x, int y, int width, int height);
void moveVehicle(Vehicle *v, int dx, int dy);
void printVehicle(Vehicle v);

#endif // VEHICLE_H
