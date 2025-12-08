#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    Vehicle car;
    char state; // 'M'=Mover, 'P'=Aparcado, 'E'=Exit
} SimVehicle;

#define MAX_CARS NUM_SPOTS
#define ENTRY_X 10
#define ENTRY_Y 1

SimVehicle allCars[MAX_CARS];
int activeCars = 0;

typedef enum { MENU, GAME } State;
State currentState = MENU;

float CAR_SPEED = 0.3f; // Un poco más rápido

// Elimina un coche del array desplazando los demás
void deleteCarAtIndex(int index) {
    for (int i = index; i < activeCars - 1; i++) {
        allCars[i] = allCars[i+1];
    }
    activeCars--;
}

void stepSimulation() {
    for (int i = 0; i < activeCars; i++) {
        SimVehicle *simCar = &allCars[i];

        // Lógica de ENTRADA
        if (simCar->state == 'M') {
            int spotIndex = simCar->car.parkedSpotIndex;
            int moved = moveVehicle(&simCar->car, spots[spotIndex].x, spots[spotIndex].y, CAR_SPEED);
            if (moved == 0) {
                occupySpot(spotIndex);
                simCar->state = 'P';
            }
        }
            // Lógica de SALIDA
        else if (simCar->state == 'E') {
            // Destino: La salida abierta abajo a la derecha (aprox X=58, Y=23)
            int targetX = 58;
            int targetY = 24; // Fuera del mapa

            int moved = moveVehicle(&simCar->car, targetX, targetY, CAR_SPEED);

            // Si el coche baja más de la fila 23, DESAPARECE
            if (simCar->car.y >= 23.0f) {
                deleteCarAtIndex(i);
                i--; // Ajustamos el índice porque hemos borrado uno
            }
        }
    }
}

void removeCarLogic() {
    // Busca el primer coche aparcado y sácalo
    for (int i = 0; i < activeCars; i++) {
        if (allCars[i].state == 'P') {
            int spotIdx = allCars[i].car.parkedSpotIndex;
            spots[spotIdx].isOccupied = 0; // Liberar plaza
            allCars[i].state = 'E'; // Cambiar a modo Salida
            return; // Solo uno por pulsación
        }
    }
}

void addNewCar() {
    if (activeCars >= MAX_CARS) return;
    int freeSpotIndex = findFreeSpot();
    if (freeSpotIndex == -1) return; // Lleno

    allCars[activeCars].car = createCar(ENTRY_X, ENTRY_Y, '=');
    allCars[activeCars].car.parkedSpotIndex = freeSpotIndex;
    allCars[activeCars].state = 'M';
    activeCars++;
}

int main(int argc, char *argv[]) {
    init_graphics();
    resetMap();

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) running = 0;

                if (currentState == MENU) {
                    if (event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_RETURN) {
                        currentState = GAME;
                        addNewCar();
                    }
                }
                else {
                    if (event.key.keysym.sym == SDLK_SPACE) addNewCar();
                    if (event.key.keysym.sym == SDLK_d) removeCarLogic();
                }
            }
        }

        if (currentState == MENU) {
            draw_menu_screen();
        } else {
            stepSimulation();
            draw_background();
            for (int i = 0; i < activeCars; i++) {
                draw_car_smooth(allCars[i].car.x, allCars[i].car.y);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    close_graphics();
    return 0;
}