#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

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
// Estados del juego
typedef enum { MENU, GAME } State;
State currentState = MENU;

void stepSimulation() {
    for (int i = 0; i < activeCars; i++) {
        SimVehicle *simCar = &allCars[i];
        if (simCar->state == 'M') {
            int spotIndex = simCar->car.parkedSpotIndex;
            int moved = moveVehicle(&simCar->car, spots[spotIndex].x, spots[spotIndex].y);
            if (moved == 0) {
                occupySpot(spotIndex);
                simCar->state = 'P';
            }
        }
    }
}

void addNewCar() {
    if (activeCars >= MAX_CARS) return;

    int freeSpotIndex = findFreeSpot();
    allCars[activeCars].car = createCar(ENTRY_X, ENTRY_Y, '=');

    if (freeSpotIndex != -1) {
        allCars[activeCars].car.parkedSpotIndex = freeSpotIndex;
        allCars[activeCars].state = 'M';
    } else {
        allCars[activeCars].car.parkedSpotIndex = -1;
        allCars[activeCars].state = 'W';
    }
    activeCars++;
}

int main(int argc, char *argv[]) {
    init_graphics();
    resetMap();
    // No añadimos coche al inicio, esperamos a que el jugador pulse espacio en el juego

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            if (event.type == SDL_KEYDOWN) {
                // CONTROLES
                if (event.key.keysym.sym == SDLK_ESCAPE) running = 0;

                if (currentState == MENU) {
                    // Pulsar 1 o Enter para empezar
                    if (event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_RETURN) {
                        currentState = GAME;
                        addNewCar(); // Añadir el primer coche al empezar
                    }
                }
                else {
                    // En Juego
                    if (event.key.keysym.sym == SDLK_SPACE) addNewCar();
                }
            }
        }

        if (currentState == MENU) {
            draw_menu_screen();
        } else {
            stepSimulation();
            draw_background(); // Dibuja mapa, carreteras y plazas

            for (int i = 0; i < activeCars; i++) {
                draw_car_graphic(allCars[i].car.x, allCars[i].car.y);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }

    close_graphics();
    return 0;
}