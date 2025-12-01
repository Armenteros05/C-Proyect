#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "map.h"
#include "vehicle.h"

// Adaptación PDF: structs para velocidad y estado
typedef struct {
    Vehicle car;
    int speed;
    char state;
} SimVehicle;

#define MAX_CARS NUM_SPOTS
#define ENTRY_X 10 // Inicio en el pasillo superior
#define ENTRY_Y 1

SimVehicle allCars[MAX_CARS];
int activeCars = 0;

void printSimulation() {
    printf("\033[H\033[J");
    printf("--- ESIEA PARKING SIMULATOR ---\n");
    printMap(); // Ahora imprime en colores!
    printf("--------------------------\n");
}

void stepSimulation() {
    for (int i = 0; i < activeCars; i++) {
        SimVehicle *simCar = &allCars[i];

        if (simCar->state == 'M') {
            int spotIndex = simCar->car.parkedSpotIndex;
            int targetX = spots[spotIndex].x;
            int targetY = spots[spotIndex].y;

            int moved = moveVehicle(&simCar->car, targetX, targetY);

            if (moved == 0) {
                occupySpot(spotIndex);
                simCar->state = 'P';
            }
        }
        drawVehicle(simCar->car);
    }
}

void addNewCar() {
    if (activeCars >= MAX_CARS) {
        printf("Parking Full!\n");
        return;
    }

    int freeSpotIndex = findFreeSpot();
    char symbol = '=';

    allCars[activeCars].car = createCar(ENTRY_X, ENTRY_Y, symbol);
    allCars[activeCars].speed = 1;

    if (freeSpotIndex != -1) {
        allCars[activeCars].car.parkedSpotIndex = freeSpotIndex;
        allCars[activeCars].state = 'M';
        drawVehicle(allCars[activeCars].car);
    } else {
        allCars[activeCars].car.parkedSpotIndex = -1;
        allCars[activeCars].state = 'W';
        drawVehicle(allCars[activeCars].car);
    }
    activeCars++;
}

int main() {
    resetMap();
    char choice = 'Y';
    addNewCar();

    printf("Welcome to the Interactive Parking Simulator.\n");

    while (toupper(choice) == 'Y') {
        int movingCarCount;
        do {
            movingCarCount = 0;
            stepSimulation();
            printSimulation();

            for (int i = 0; i < activeCars; i++) {
                if (allCars[i].state == 'M') movingCarCount++;
            }
            if (movingCarCount > 0) usleep(80000);
        } while (movingCarCount > 0);

        printf("\n--- ACTION ---\n");
        printf("Spawn Car? (Y/N): ");
        if (scanf(" %c", &choice) != 1) choice = 'N';
        if (toupper(choice) == 'Y') addNewCar();
    }
    printf("\nFin.\n");
    return 0;
}