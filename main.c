#include "map.h"
#include "vehicle.h"

int main() {
    resetMap();

    Vehicle v1 = createCarSmall(10, 5);
    Vehicle v2 = createCarLarge(20, 10);

    drawVehicle(v1);
    drawVehicle(v2);

    printMap();

    return 0;
}
