#include "graphics.h"
#include <stdio.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

#define ROAD_1_X 6
#define ROAD_2_X 24
#define ROAD_3_X 40

void init_graphics() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) exit(1);
    window = SDL_CreateWindow("ESIEA Parking Simulator v3.0",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT + 40, SDL_WINDOW_SHOWN);
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

void draw_dashed_line(int x) {
    int px = x * TILE_SIZE;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
    for (int y = 0; y < SCREEN_HEIGHT; y += 40) {
        if (y > (4 * TILE_SIZE)) {
            SDL_Rect dash = { px, y, 4, 20 };
            SDL_RenderFillRect(renderer, &dash);
        }
    }
}

void draw_menu_screen() {
    SDL_SetRenderDrawColor(renderer, 20, 20, 25, 255);
    SDL_RenderClear(renderer);
    // Botón verde simple
    draw_box_pixels((SCREEN_WIDTH/2)-80, (SCREEN_HEIGHT/2)-25, 160, 50, 0, 180, 0, 255);
}

void draw_background() {
    SDL_SetRenderDrawColor(renderer, 45, 45, 50, 255); // Asfalto
    SDL_RenderClear(renderer);

    draw_dashed_line(ROAD_1_X);
    draw_dashed_line(ROAD_2_X);
    draw_dashed_line(ROAD_3_X);

    // DIBUJAR PLAZAS (MEJORADAS)
    for (int i = 0; i < NUM_SPOTS; i++) {
        int cX = spots[i].x * TILE_SIZE;
        int cY = spots[i].y * TILE_SIZE + 40;

        int w = (TILE_SIZE * 3) + 4;
        int h = TILE_SIZE + 4;
        int xStart = cX - (TILE_SIZE + 2);
        int yStart = cY - (TILE_SIZE / 2) - 2;

        // A) LÍNEAS GRUESAS (Usamos rectángulos finos en vez de líneas)
        int thickness = 3; // Grosor de 3 píxeles

        // Línea Superior
        draw_box_pixels(xStart, yStart, w, thickness, 255, 255, 255, 255);
        // Línea Inferior
        draw_box_pixels(xStart, yStart + h, w, thickness, 255, 255, 255, 255);
        // Línea Trasera (Fondo)
        draw_box_pixels(xStart + w, yStart, thickness, h + thickness, 255, 255, 255, 255);

        // B) PILOTO FUERA DE LA PLAZA
        // Lo subimos por encima de la línea superior (yStart - 15 pixeles)
        int pX = cX + TILE_SIZE;
        int pY = yStart - 12; // Fuera del cajón, hacia el pasillo

        // Base del piloto (gris oscuro)
        draw_box_pixels(pX-2, pY-2, 12, 12, 20, 20, 20, 255);

        // Luz
        if (spots[i].isOccupied) {
            draw_box_pixels(pX, pY, 8, 8, 255, 0, 0, 255); // ROJO
        } else {
            draw_box_pixels(pX, pY, 8, 8, 0, 255, 0, 255); // VERDE
        }
    }

    // DIBUJAR MUROS (Después de las plazas para que tapen imperfecciones)
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            char cell = asciiMap[y][x];
            int pX = x * TILE_SIZE;
            int pY = y * TILE_SIZE + 40;

            if (cell == '#') {
                draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 139, 69, 19, 255);
                SDL_SetRenderDrawColor(renderer, 0,0,0,255);
                SDL_Rect border = {pX, pY, TILE_SIZE, TILE_SIZE};
                SDL_RenderDrawRect(renderer, &border);
            }
            else if (cell == 'E') draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 0, 100, 0, 150);
            else if (cell == 'X') draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 100, 0, 0, 150);
        }
    }

    // HUD
    draw_box_pixels(0, 0, SCREEN_WIDTH, 40, 30, 30, 30, 255);
    draw_box_pixels(0, 38, SCREEN_WIDTH, 2, 255, 215, 0, 255);
}

void draw_car_graphic(int x, int y) { // x, y ahora son visuales (convertidos en main)
    // El 'main' nos pasará coordenadas ya convertidas a píxeles o casi
    // Pero como graphics recibe enteros, haremos el ajuste fino aquí

    // NOTA: Como 'x' viene de un float casteado, ya es el tile index.
    // Necesitamos dibujar en Píxeles.
    // El truco es que main.c llamará a esta función pasando (int)v.x y (int)v.y
    // Pero para suavidad REAL, deberíamos pasar floats a esta función.
    // Por simplicidad, usaremos el mismo cálculo:

    // ERROR CORRECCIÓN: Si main pasa el índice del tile, el movimiento se verá a saltos.
    // Vamos a cambiar el prototipo en graphics.h para aceptar float.
}

// NUEVA FUNCIÓN QUE ACEPTA FLOATS
void draw_car_smooth(float x, float y) {
    int pX = (int)(x * TILE_SIZE) - TILE_SIZE; // Ajuste de centro
    int pY = (int)(y * TILE_SIZE) + 40 - 8;    // Ajuste vertical

    // Sombra
    draw_box_pixels(pX + 4, pY + 4, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 0, 0, 0, 100);
    // Carrocería
    draw_box_pixels(pX + 2, pY + 2, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 255, 200, 0, 255);
    // Cristal
    draw_box_pixels(pX + TILE_SIZE, pY + 5, TILE_SIZE, TILE_SIZE - 10, 50, 100, 200, 255);
}