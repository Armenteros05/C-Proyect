#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "map.h"
#include "vehicle.h"
#include "colors.h"


typedef struct {
    Vehicle car;
    int speed;
    char state;
} SimVehicle;

#define MAX_CARS NUM_SPOTS
#define ENTRY_X 10
#define ENTRY_Y 1

SimVehicle allCars[MAX_CARS];
int activeCars = 0;
int gameMode = 1; // 1: Smooth, 2: Busy

// --- PANTALLA DE INICIO / MENÚ ---
void showMainMenu() {
    system("clear"); // O "cls" en Windows
    printf("\n");
    printf(FG_CYAN "  ____            _     ____  _           \n");
    printf(" |  _ \\ __ _ _ __| | __/ ___|(_)_ __ ___  \n");
    printf(" | |_) / _` | '__| |/ /\\___ \\| | '_ ` _ \\ \n");
    printf(" |  __/ (_| | |  |   <  ___) | | | | | | |\n");
    printf(" |_|   \\__,_|_|  |_|\\_\\|____/|_|_| |_| |_|\n" RESET);
    printf("\n");
    printf("         " BG_BLUE " WELCOME TO PARKSIM 2025 " RESET "\n\n");
    printf(" Select Game Mode:\n");
    printf(" [1] " FG_GREEN "Smooth Mode" RESET " (Normal Traffic)\n");
    printf(" [2] " FG_RED "Busy Mode" RESET "   (High Traffic - Coming Soon)\n");
    printf("\n > Enter choice: ");
}

void printSimulation() {
    printf("\033[H\033[J");
    printf("--- PARKSIM: %s Mode ---\n", (gameMode == 1) ? "Smooth" : "Busy");
    printMap();
    printf("--------------------------------------------------------------\n");
}

void stepSimulation() {
    for (int i = 0; i < activeCars; i++) {
        SimVehicle *simCar = &allCars[i];

        if (simCar->state == 'M') {
            int spotIndex = simCar->car.parkedSpotIndex;
            int targetX = spots[spotIndex].x;
            int targetY = spots[spotIndex].y;

            int moved = moveVehicle(&simCar->car, targetX, targetY, 1.0f);


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
        printf(FG_RED "Parking Full!\n" RESET);
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
    // 1. MOSTRAR MENÚ
    showMainMenu();
    int choice;
    if (scanf("%d", &choice) != 1) choice = 1;

    if (choice == 2) {
        gameMode = 2;
        printf("Busy mode selected (Logic pending implementation). Starting Smooth...\n");
                sleep(2);
    } else {
        gameMode = 1;
    }

    // 2. INICIAR SIMULACIÓN
    resetMap();
    char action = 'Y';
    addNewCar();

    while (toupper(action) == 'Y') {
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

        printf("\n " BG_WHITE FG_BLUE " ACTION " RESET " Spawn new car? (Y/N): ");
        if (scanf(" %c", &action) != 1) action = 'N';
        if (toupper(action) == 'Y') addNewCar();
    }
    printf("\nSimulation finished.\n");
    return 0;
}