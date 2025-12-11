#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include "sound.h"
int motorSoundPlaying = 0;



typedef struct {
    Vehicle car;
    char state; // 'M'=Mover, 'P'=Aparcado, 'E'=Exit
} SimVehicle;

#define MAX_CARS NUM_SPOTS
#define ENTRY_X 10
#define ENTRY_Y 1

SimVehicle allCars[MAX_CARS];
int activeCars = 0;

typedef enum { MENU, GAME, GAME_BUSY } State;

State currentState = MENU;

float CAR_SPEED = 0.3f; // Un poco más rápido

// Elimina un coche del array desplazando los demás
void deleteCarAtIndex(int index) {
    for (int i = index; i < activeCars - 1; i++) {
        allCars[i] = allCars[i+1];
    }
    activeCars--;
}
void resetGame() {
    activeCars = 0;            // Tüm arabaları sıfırla
    resetMap();                // Park yerlerini sıfırla
    stopAllSounds();           // Bütün sesleri durdur
}

void stepSimulation() {
    int anyCarMoving = 0;

    for (int i = 0; i < activeCars; i++) {
        SimVehicle *simCar = &allCars[i];

        if (simCar->state == 'M') {
            int spotIndex = simCar->car.parkedSpotIndex;
            int moved = moveVehicle(&simCar->car,
                                    spots[spotIndex].x,
                                    spots[spotIndex].y,
                                    CAR_SPEED);

            if (moved != 0) anyCarMoving = 1;

            if (moved == 0) {
                occupySpot(spotIndex);
                simCar->state = 'P';
            }
        }
        else if (simCar->state == 'E') {
            int moved = moveVehicle(&simCar->car, 58, 24, CAR_SPEED);

            if (moved != 0) anyCarMoving = 1;

            if (simCar->car.y >= 23.0f) {
                deleteCarAtIndex(i);
                i--;
            }
        }
    }

    // Motor sesi kontrolü
    if (anyCarMoving && !motorSoundPlaying) {
        playLooped("Sounds/motor.wav");
        motorSoundPlaying = 1;
    }

    if (!anyCarMoving && motorSoundPlaying) {
        stopAllSounds();
        motorSoundPlaying = 0;
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

    // RESERVIEREN: verhindert, dass ein weiteres Auto denselben Platz wählt,
    // bevor dieses Auto angekommen / als besetzt markiert ist.
    reserveSpot(freeSpotIndex);

    allCars[activeCars].car = createCar(ENTRY_X, ENTRY_Y, '=');
    allCars[activeCars].car.parkedSpotIndex = freeSpotIndex;
    allCars[activeCars].state = 'M';
    activeCars++;


    playSound("Sounds/motor.wav");
    playSound("Sounds/ping.wav");
}

int main(int argc, char *argv[]) {
    init_graphics();
    resetMap();
    playSound("Sounds/menu.wav");

    int running = 1;
    SDL_Event event;

    Uint32 lastAutoAdd = 0;
    Uint32 lastAutoRemove = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) running = 0;

                // MENU CONTROLS
                if (currentState == MENU) {
                    if (event.key.keysym.sym == SDLK_1) {
                        stopAllSounds();
                        currentState = GAME;
                        addNewCar();
                    }
                    if (event.key.keysym.sym == SDLK_2) {
                        stopAllSounds();
                        currentState = GAME_BUSY;

                        lastAutoAdd = SDL_GetTicks();
                        lastAutoRemove = SDL_GetTicks();
                    }
                }
                // GAME MODE KEYBINDS (manuel)
                else if (currentState == GAME) {
                    if (event.key.keysym.sym == SDLK_SPACE) addNewCar();
                    if (event.key.keysym.sym == SDLK_d) removeCarLogic();
                    if (event.key.keysym.sym == SDLK_m) {
                        stopAllSounds();
                        resetGame();
                        currentState = MENU;
                        playSound("Sounds/menu.wav");
                    }
                }
                else if (currentState == GAME_BUSY) {
                    if (event.key.keysym.sym == SDLK_m) {
                        stopAllSounds();
                        resetGame();
                        currentState = MENU;
                        playSound("Sounds/menu.wav");
                    }
                }

            }
        }

        // ============================
        // MODE: MENU
        // ============================
        if (currentState == MENU) {
            draw_menu_screen();
        }

        // ============================
        // MODE: EASY / NORMAL
        // ============================
        else if (currentState == GAME) {
            stepSimulation();
            draw_background();
            for (int i = 0; i < activeCars; i++)
                draw_car_smooth(allCars[i].car.x, allCars[i].car.y);
        }

        // ============================
        // MODE: BUSY (OTOMATIK)
        // ============================
        else if (currentState == GAME_BUSY) {

            Uint32 now = SDL_GetTicks();

            // Her 700 ms'de otomatik araba ekle (hızlı trafik)
            if (now - lastAutoAdd > 700) {
                addNewCar();
                lastAutoAdd = now;
            }

            // Her 1500 ms'de araba çıkar
            if (now - lastAutoRemove > 1500) {
                removeCarLogic();
                lastAutoRemove = now;
            }

            // Normal sim çalıştır
            stepSimulation();

            // Çiz
            draw_background();
            for (int i = 0; i < activeCars; i++)
                draw_car_smooth(allCars[i].car.x, allCars[i].car.y);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    stopAllSounds();
    close_graphics();
    return 0;
}
