#include "graphics.h"
#include <stdio.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void init_graphics() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error SDL: %s\n", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("ESIEA Parking Simulator (SDL2)",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void close_graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Ayuda para dibujar rectángulos rellenos
void draw_rect_fill(int x, int y, int w, int h, int r, int g, int b, int a) {
    SDL_Rect rect = {x * TILE_SIZE, y * TILE_SIZE, w * TILE_SIZE, h * TILE_SIZE};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Para transparencia
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &rect);
}

void draw_background() {
    // 1. Limpiar pantalla (Negro)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // 2. DIBUJAR MAPA BASE (Muros y Carreteras)
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            char cell = asciiMap[y][x];

            if (cell == '.') {
                // Carretera: Gris Oscuro
                draw_rect_fill(x, y, 1, 1, 60, 60, 60, 255);
            }
            else if (cell == '+' || cell == '-' || cell == '|' || cell == '=') {
                // Muros: Blanco/Gris Claro
                draw_rect_fill(x, y, 1, 1, 200, 200, 200, 255);
            }
        }
    }

    // 3. DIBUJAR PLAZAS (Luces Verde/Rojo)
    for (int i = 0; i < NUM_SPOTS; i++) {
        // La plaza visual mide 7 de ancho x 3 de alto
        int w = 7;
        int h = 3;
        // Ajustamos la posición X,Y (spots[i] es el centro, restamos para ir a la esquina)
        int drawX = spots[i].x - 3;
        int drawY = spots[i].y - 1;

        if (spots[i].isOccupied) {
            // ROJO SEMITRANSPARENTE (Ocupado)
            draw_rect_fill(drawX, drawY, w, h, 255, 0, 0, 100);
        } else {
            // VERDE SEMITRANSPARENTE (Libre)
            draw_rect_fill(drawX, drawY, w, h, 0, 255, 0, 50);
        }
    }
}

void draw_car_graphic(int x, int y) {
    // El coche mide 3 tiles de ancho. Dibujamos desde x-1
    int drawX = x - 1;

    // Chasis (Amarillo Deportivo)
    draw_rect_fill(drawX, y, 3, 1, 255, 215, 0, 255);

    // Techo/Cristal (Azul oscuro en el centro)
    draw_rect_fill(x, y, 1, 1, 0, 0, 100, 200);
}