#include <stdio.h>
#include <stdlib.h>
#include <windows.h>   // Sleep()
#include "vehicle.h"
#include "map.h"

int main() {
    // Initialize map
    resetMap();

    // Create vehicles
    Vehicle v1 = createCarSmall(1, 5, 5);
    Vehicle v2 = createCarLarge(2, 10, 10);

    while (1) {
        system("cls");  // clear screen
        resetMap();     // reset map for new draw

        drawVehicle(v1, parkingMap);
        drawVehicle(v2, parkingMap);

        printMap();     // print updated map

        // Move vehicles
        moveVehicle(&v1, 1, 0);
        moveVehicle(&v2, 0, 1);

        Sleep(200);     // 200 ms
    }

    return 0;
}
