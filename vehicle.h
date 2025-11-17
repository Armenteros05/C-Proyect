#ifndef VEHICLE_H
#define VEHICLE_H

typedef enum {
    SMALL,
    LARGE
} VehicleType;

typedef struct {
    int x;
    int y;
    VehicleType type;
    char symbol;
} Vehicle;

Vehicle createCarSmall(int x, int y);
Vehicle createCarLarge(int x, int y);

void drawVehicle(Vehicle v);

#endif
