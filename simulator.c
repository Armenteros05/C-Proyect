#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "map.h"
#include "vehicle.h"

// Vehicle state definitions
typedef enum {
    STATE_PARKED,
    STATE_MOVING_TO_SPOT,
    STATE_WAITING_FOR_SPOT
} VehicleState;

typedef struct {
    Vehicle car;
    VehicleState state;
} SimVehicle;

#define MAX_CARS 20
#define ENTRY_X 10
#define ENTRY_Y 1

SimVehicle allCars[MAX_CARS];
int activeCars = 0;

void printSimulation() {
    printf("\033[H\033[J"); // Clears the console
    printf("--- PARKING SIMULATOR ---\n");
    printMap();
    printf("\n--- Status ---\n");
    for (int i = 0; i < activeCars; i++) {
        printf("Car %c (Index %d): ", allCars[i].car.symbol, i + 1);

        switch (allCars[i].state) {
            case STATE_PARKED:
                printf("PARKED at spot %d (X:%d, Y:%d)\n",
                       allCars[i].car.parkedSpotIndex,
                       allCars[i].car.x,
                       allCars[i].car.y);
                break;
            case STATE_MOVING_TO_SPOT:
                printf("MOVING to spot %d (Target X:%d, Y:%d)\n",
                       allCars[i].car.parkedSpotIndex,
                       spots[allCars[i].car.parkedSpotIndex].x,
                       spots[allCars[i].car.parkedSpotIndex].y);
                break;
            case STATE_WAITING_FOR_SPOT:
                printf("WAITING (No spot available)\n");
                break;
        }
    }
    printf("--------------------------\n");
}

void stepSimulation() {
    for (int i = 0; i < activeCars; i++) {
        SimVehicle *simCar = &allCars[i];

        if (simCar->state == STATE_MOVING_TO_SPOT) {
            int spotIndex = simCar->car.parkedSpotIndex;
            int targetX = spots[spotIndex].x;
            int targetY = spots[spotIndex].y;

            // Move the vehicle one step
            int moved = moveVehicle(&simCar->car, targetX, targetY);

            if (moved == 0) {
                // The car has arrived precisely at the spot coordinates.
                occupySpot(spotIndex); // Mark the spot as occupied
                simCar->state = STATE_PARKED;
            }
        }

        // Redraw parked cars to ensure they remain visible
        if (simCar->state == STATE_PARKED) {
            drawVehicle(simCar->car);
        }
    }
}

void addNewCar() {
    if (activeCars >= MAX_CARS) {
        printf("Maximum number of cars (%d) reached. Cannot add more.\n", MAX_CARS);
        return;
    }

    int freeSpotIndex = findFreeSpot();
    char symbol = 'A' + activeCars;

    allCars[activeCars].car = createCar(ENTRY_X, ENTRY_Y, symbol);

    if (freeSpotIndex != -1) {
        allCars[activeCars].car.parkedSpotIndex = freeSpotIndex;
        allCars[activeCars].state = STATE_MOVING_TO_SPOT;
        drawVehicle(allCars[activeCars].car);
        printf("Car %c has entered the lot, heading to spot %d.\n", symbol, freeSpotIndex);
    } else {
        allCars[activeCars].car.parkedSpotIndex = -1;
        allCars[activeCars].state = STATE_WAITING_FOR_SPOT;
        drawVehicle(allCars[activeCars].car);
        printf("Car %c has entered the lot but no free spot was found. Waiting...\n", symbol);
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
                usleep(100000); // 0.1 second pause for visualization
            }
        } while (movingCarCount > 0);

        printf("\n--- ACTION ---\n");
        printf("Do you want to introduce a new car? (Y/N): ");

        if (scanf(" %c", &choice) != 1) {
            choice = 'N';
        }

        if (toupper(choice) == 'Y') {
            addNewCar();
        }
    }

    printf("\nSimulation finished. Goodbye!\n");
    return 0;
}