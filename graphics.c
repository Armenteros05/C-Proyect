#include "graphics.h"
#include <stdio.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void init_graphics() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error SDL: %s\n", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("ESIEA Parking Simulator (Final)",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void close_graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_box_pixels(int pixelX, int pixelY, int w, int h, int r, int g, int b, int a) {
    SDL_Rect rect = {pixelX, pixelY, w, h};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &rect);
}

void draw_background() {
    // 1. FONDO ASFALTO (Gris oscuro limpio)
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderClear(renderer);

    // 2. DIBUJAR MAPA (Solo Muros y Zonas Especiales)
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            char cell = asciiMap[y][x];
            int pX = x * TILE_SIZE;
            int pY = y * TILE_SIZE;

            if (cell == '#') {
                // MURO (Ladrillo)
                draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 120, 60, 30, 255);
                // Borde negro
                SDL_SetRenderDrawColor(renderer, 0,0,0,255);
                SDL_Rect b = {pX, pY, TILE_SIZE, TILE_SIZE};
                SDL_RenderDrawRect(renderer, &b);
            }
            else if (cell == 'E') {
                // ENTRADA (Texto E pintado en suelo)
                draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 0, 100, 0, 255);
            }
            else if (cell == 'X') {
                // SALIDA
                draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 100, 0, 0, 255);
            }
        }
    }

    // 3. DIBUJAR PLAZAS (ESTILO LÍNEAS)
    for (int i = 0; i < NUM_SPOTS; i++) {
        int cX = spots[i].x * TILE_SIZE;
        int cY = spots[i].y * TILE_SIZE;

        // Dimensiones de la plaza (aprox 3 bloques de ancho x 1.5 alto)
        int w = (TILE_SIZE * 3) + 12;
        int h = TILE_SIZE + 6;
        int xStart = cX - (TILE_SIZE + 6); // Empezamos un poco a la izquierda del centro
        int yStart = cY - (TILE_SIZE / 2) - 3;

        // A) PINTAR LÍNEAS BLANCAS (La "U" o cajón)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Línea Superior
        SDL_RenderDrawLine(renderer, xStart, yStart, xStart + w, yStart);
        // Línea Inferior
        SDL_RenderDrawLine(renderer, xStart, yStart + h, xStart + w, yStart + h);
        // Línea Trasera (Derecha) -> Cierra la plaza por el fondo
        SDL_RenderDrawLine(renderer, xStart + w, yStart, xStart + w, yStart + h);

        // La izquierda se queda abierta para entrar

        // B) SENSOR LED (Círculo/Cuadrado pequeño en el centro-fondo)
        int pilotSize = 8;
        int pX = cX + TILE_SIZE + 5;
        int pY = cY; // Centrado verticalmente

        if (spots[i].isOccupied) {
            // ROJO
            draw_box_pixels(pX, pY, pilotSize, pilotSize, 255, 50, 50, 255);
        } else {
            // VERDE
            draw_box_pixels(pX, pY, pilotSize, pilotSize, 50, 255, 50, 255);
        }
    }
}

void draw_car_graphic(int x, int y) {
    // Dibujo del coche simple pero efectivo
    int pX = (x - 1) * TILE_SIZE;
    int pY = y * TILE_SIZE;

    // Sombra
    draw_box_pixels(pX + 4, pY + 4, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 0, 0, 0, 100);

    // Carrocería
    draw_box_pixels(pX + 2, pY + 2, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 255, 215, 0, 255); // Amarillo

    // Cristal
    draw_box_pixels(pX + TILE_SIZE, pY + 4, TILE_SIZE, TILE_SIZE - 8, 50, 50, 200, 255);
}