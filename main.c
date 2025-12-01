#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para delays o randoms si quisieras

// Estructura compatible con el PDF (voiture)
typedef struct {
    Vehicle car;
    int speed;
    char state; // 'M' = Moving, 'P' = Parked, 'W' = Waiting
} SimVehicle;

#define MAX_CARS NUM_SPOTS
#define ENTRY_X 10
#define ENTRY_Y 1

SimVehicle allCars[MAX_CARS];
int activeCars = 0;

void stepSimulation() {
    for (int i = 0; i < activeCars; i++) {
        SimVehicle *simCar = &allCars[i];

        if (simCar->state == 'M') {
            int spotIndex = simCar->car.parkedSpotIndex;
            int targetX = spots[spotIndex].x;
            int targetY = spots[spotIndex].y;

            // Movemos el coche
            int moved = moveVehicle(&simCar->car, targetX, targetY);

            // Si devuelve 0, es que ha llegado
            if (moved == 0) {
                occupySpot(spotIndex);
                simCar->state = 'P'; // Parked
            }
        }
    }
}

void addNewCar() {
    if (activeCars >= MAX_CARS) {
        printf("Parking Completo!\n");
        return;
    }

    int freeSpotIndex = findFreeSpot();
    char symbol = '='; // Símbolo lógico

    allCars[activeCars].car = createCar(ENTRY_X, ENTRY_Y, symbol);
    allCars[activeCars].speed = 1;

    if (freeSpotIndex != -1) {
        allCars[activeCars].car.parkedSpotIndex = freeSpotIndex;
        allCars[activeCars].state = 'M'; // Empezar a moverse
        printf("Coche %d asignado a plaza %d\n", activeCars, freeSpotIndex);
    } else {
        allCars[activeCars].car.parkedSpotIndex = -1;
        allCars[activeCars].state = 'W'; // Esperar
        printf("Coche %d en espera (Parking lleno)\n", activeCars);
    }
    activeCars++;
}

// MAIN PARA SDL (requiere argc, argv)
int main(int argc, char *argv[]) {

    // 1. Inicializar
    init_graphics();
    resetMap();
    addNewCar(); // Añadimos el primero automáticamente

    int running = 1;
    SDL_Event event;

    // 2. Bucle del Juego
    while (running) {

        // A. EVENTOS (Input)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                // ESPACIO para añadir coche
                if (event.key.keysym.sym == SDLK_SPACE) {
                    addNewCar();
                }
                // ESC para salir
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
            }
        }

        // B. LÓGICA (Actualizar posiciones)
        stepSimulation();

        // C. RENDERIZADO (Dibujar)
        // 1. Dibujar el fondo (mapa + plazas)
        draw_background();

        // 2. Dibujar los coches encima
        for (int i = 0; i < activeCars; i++) {
            draw_car_graphic(allCars[i].car.x, allCars[i].car.y);
        }

        // 3. Mostrar lo dibujado
        SDL_RenderPresent(renderer);

        // 4. Pequeña pausa para controlar la velocidad (aprox 60 FPS)
        SDL_Delay(50);
    }

    // 3. Limpieza
    close_graphics();
    return 0;
}