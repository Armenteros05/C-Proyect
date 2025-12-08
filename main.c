#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    Vehicle car;
    char state; // 'M'=Mover, 'P'=Aparcado, 'E'=Exit (Saliendo)
} SimVehicle;

#define MAX_CARS NUM_SPOTS
#define ENTRY_X 10
#define ENTRY_Y 1
#define EXIT_X 60  // Coordenada X de la salida (aprox)
#define EXIT_Y 23  // Coordenada Y de la salida (abajo del todo)

SimVehicle allCars[MAX_CARS];
int activeCars = 0;

typedef enum { MENU, GAME } State;
State currentState = MENU;

// Velocidad del coche (0.2 = lento y suave, 0.5 = rápido)
float CAR_SPEED = 0.25f;

void removeCarLogic() {
    // Buscar un coche aparcado ('P') y mandarlo a la salida
    for (int i = 0; i < activeCars; i++) {
        if (allCars[i].state == 'P') {
            // Liberar la plaza
            int spotIdx = allCars[i].car.parkedSpotIndex;
            spots[spotIdx].isOccupied = 0; // ¡Luz verde!

            // Cambiar estado a Saliendo
            allCars[i].state = 'E';
            return; // Solo sacamos uno cada vez que pulsas D
        }
    }
}

void stepSimulation() {
    for (int i = 0; i < activeCars; i++) {
        SimVehicle *simCar = &allCars[i];

        // Lógica de ENTRADA
        if (simCar->state == 'M') {
            int spotIndex = simCar->car.parkedSpotIndex;
            int moved = moveVehicle(&simCar->car, spots[spotIndex].x, spots[spotIndex].y, CAR_SPEED);
            if (moved == 0) {
                occupySpot(spotIndex); // Luz roja
                simCar->state = 'P';
            }
        }
            // Lógica de SALIDA (Exit)
        else if (simCar->state == 'E') {
            // Objetivo: Ir abajo a la derecha
            // Usamos la misma lógica de movimiento pero hacia la salida
            // Truco: movemos el coche hacia la carretera vertical más cercana y luego abajo
            int targetX = 58; // Cerca de la salida X en el mapa
            int targetY = 22; // Abajo del todo

            int moved = moveVehicle(&simCar->car, targetX, targetY, CAR_SPEED);

            // Si llega a la salida, lo "teletransportamos" fuera (o borramos)
            if (moved == 0) {
                simCar->car.x = -10; // Lo sacamos de la pantalla
                // Aquí podrías implementar lógica para eliminarlo del array
            }
        }
    }
}

void addNewCar() {
    if (activeCars >= MAX_CARS) return;

    int freeSpotIndex = findFreeSpot();
    // Si no hay sitio, no entra
    if (freeSpotIndex == -1) return;

    allCars[activeCars].car = createCar(ENTRY_X, ENTRY_Y, '=');
    allCars[activeCars].car.parkedSpotIndex = freeSpotIndex;
    allCars[activeCars].state = 'M';

    // Opcional: Reservar visualmente la plaza ya (Luz roja)
    // O esperar a que llegue (lo hacemos al llegar en stepSimulation)

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
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        currentState = GAME;
                        addNewCar();
                    }
                }
                else {
                    // ESPACIO: Nuevo Coche
                    if (event.key.keysym.sym == SDLK_SPACE) addNewCar();
                    // D: Salir Coche (Depart)
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
                // Usamos la nueva función suave
                draw_car_smooth(allCars[i].car.x, allCars[i].car.y);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS para que se vea muy fluido
    }

    close_graphics();
    return 0;
}