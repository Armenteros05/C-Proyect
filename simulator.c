#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "map.h"
#include "vehicle.h"

typedef enum {
    STATE_PARKED,
    STATE_MOVING_TO_SPOT,
    STATE_WAITING_FOR_SPOT
} VehicleState;

typedef struct {
    Vehicle car;
    VehicleState state;
} SimVehicle;

#define MAX_CARS NUM_SPOTS // Ahora 15
#define ENTRY_X 10
#define ENTRY_Y 2  // Pasillo de entrada

SimVehicle allCars[MAX_CARS];
int activeCars = 0;

void printSimulation() {
    printf("\033[H\033[J");
    printf("--- PARKING SIMULATOR (%d Plazas Isla) ---\n", NUM_SPOTS);
    printMap();
    printf("--------------------------\n");
}

void stepSimulation() {
    for (int i = 0; i < activeCars; i++) {
        SimVehicle *simCar = &allCars[i];

        if (simCar->state == STATE_MOVING_TO_SPOT) {
            int spotIndex = simCar->car.parkedSpotIndex;
            int targetX = spots[spotIndex].x;
            int targetY = spots[spotIndex].y;

            int moved = moveVehicle(&simCar->car, targetX, targetY);

            if (moved == 0) {
                occupySpot(spotIndex);
                simCar->state = STATE_PARKED;
            }
        }

        if (simCar->state == STATE_PARKED) {
            drawVehicle(simCar->car);
        }
    }
}

void addNewCar() {
    if (activeCars >= MAX_CARS) {
        printf("Parking Completo!\n");
        return;
    }

    int freeSpotIndex = findFreeSpot();

    // Coche [=]
    char symbol = '=';

    allCars[activeCars].car = createCar(ENTRY_X, ENTRY_Y, symbol);

    if (freeSpotIndex != -1) {
        allCars[activeCars].car.parkedSpotIndex = freeSpotIndex;
        allCars[activeCars].state = STATE_MOVING_TO_SPOT;
        drawVehicle(allCars[activeCars].car);
    } else {
        allCars[activeCars].car.parkedSpotIndex = -1;
        allCars[activeCars].state = STATE_WAITING_FOR_SPOT;
        drawVehicle(allCars[activeCars].car);
        printf("Coche en espera...\n");
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
                if (allCars[i].state == STATE_MOVING_TO_SPOT) {
                    movingCarCount++;
                }
            }
            if (movingCarCount > 0) {
                usleep(80000);
            }
        } while (movingCarCount > 0);

        printf("\n--- ACCION ---\n");
        printf("Nuevo coche? (Y/N): ");

        if (scanf(" %c", &choice) != 1) choice = 'N';
        if (toupper(choice) == 'Y') addNewCar();
    }

    printf("\nFin de simulacion.\n");
    return 0;
}