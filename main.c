#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "map.h"
#include "vehicle.h"

int main() {
    resetMap();

    Vehicle car = createCar(5, 5, 'C');
    drawVehicle(car);

    while (1) {
        system("cls"); // Windows console refresh
        printMap();

        int newX = car.x + 1;
        int newY = car.y;

        if (newX >= MAP_COLS - 1) newX = 1; // wrap around

        moveVehicle(&car, newX, newY);

        usleep(100000); // 0.1 sec
    }

    return 0;
}
