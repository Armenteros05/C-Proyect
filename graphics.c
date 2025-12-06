#include "graphics.h"
#include <stdio.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Definición de las columnas de carretera (coinciden con vehicle.c)
#define ROAD_1_X 6
#define ROAD_2_X 24
#define ROAD_3_X 40

void init_graphics() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error SDL: %s\n", SDL_GetError());
        exit(1);
    }
    // Aumentamos un poco el alto (+40px) para la barra de interfaz superior
    window = SDL_CreateWindow("ESIEA Parking Simulator v2.0",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT + 40, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void close_graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Dibuja un rectángulo relleno
void draw_box_pixels(int pixelX, int pixelY, int w, int h, int r, int g, int b, int a) {
    SDL_Rect rect = {pixelX, pixelY, w, h};
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &rect);
}

// Dibuja líneas discontinuas (Carretera)
void draw_dashed_line(int x) {
    int px = x * TILE_SIZE;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200); // Blanco transparente

    for (int y = 0; y < SCREEN_HEIGHT; y += 40) {
        // Solo dibujamos si no estamos encima de un muro horizontal
        if (y > (4 * TILE_SIZE)) {
            SDL_Rect dash = { px, y, 4, 20 }; // Línea de 4px ancho, 20px alto
            SDL_RenderFillRect(renderer, &dash);
        }
    }
}

// --- DIBUJAR MENÚ ---
void draw_menu_screen() {
    // Fondo Azul Oscuro Tecnológico
    SDL_SetRenderDrawColor(renderer, 10, 20, 40, 255);
    SDL_RenderClear(renderer);

    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;

    // TÍTULO SIMULADO (Bloques grandes)
    // "P"
    draw_box_pixels(centerX - 100, centerY - 100, 20, 80, 255, 215, 0, 255);
    draw_box_pixels(centerX - 100, centerY - 100, 60, 20, 255, 215, 0, 255);
    draw_box_pixels(centerX - 100, centerY - 60, 60, 20, 255, 215, 0, 255);
    draw_box_pixels(centerX - 40, centerY - 100, 20, 60, 255, 215, 0, 255);

    // BOTÓN "START" (Verde)
    draw_box_pixels(centerX - 80, centerY + 50, 160, 50, 0, 200, 0, 255);
    // Texto "S" simulado dentro del botón
    draw_box_pixels(centerX - 10, centerY + 65, 20, 20, 255, 255, 255, 255);

    // Instrucciones
    // Simulamos texto con líneas finas
    draw_box_pixels(centerX - 60, centerY + 120, 120, 2, 200, 200, 200, 255);
    draw_box_pixels(centerX - 60, centerY + 130, 120, 2, 200, 200, 200, 255);
}

// --- DIBUJAR JUEGO ---
void draw_background() {
    // 1. Limpiar pantalla (Gris Asfalto Limpio)
    SDL_SetRenderDrawColor(renderer, 45, 45, 50, 255);
    SDL_RenderClear(renderer);

    // 2. DIBUJAR CARRILES (Líneas discontinuas)
    // Dibujamos en los carriles definidos para que el usuario vea el camino
    draw_dashed_line(ROAD_1_X);
    draw_dashed_line(ROAD_2_X);
    draw_dashed_line(ROAD_3_X);

    // 3. DIBUJAR MAPA (Muros y Zonas)
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            char cell = asciiMap[y][x];
            int pX = x * TILE_SIZE;
            int pY = y * TILE_SIZE + 40; // +40 por la barra superior

            if (cell == '#') {
                // MURO 3D (Dos tonos)
                draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 160, 82, 45, 255); // Cara frontal
                draw_box_pixels(pX, pY+TILE_SIZE-5, TILE_SIZE, 5, 100, 50, 20, 255); // Sombra base
                // Borde negro
                SDL_SetRenderDrawColor(renderer, 0,0,0,255);
                SDL_Rect border = {pX, pY, TILE_SIZE, TILE_SIZE};
                SDL_RenderDrawRect(renderer, &border);
            }
            else if (cell == 'E') {
                // ENTRADA (Franjas amarillas de precaución)
                draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 50, 50, 50, 255); // Fondo
                draw_box_pixels(pX+5, pY+5, TILE_SIZE-10, TILE_SIZE-10, 255, 255, 0, 200);
            }
            else if (cell == 'X') {
                // SALIDA
                draw_box_pixels(pX+5, pY+5, TILE_SIZE-10, TILE_SIZE-10, 200, 0, 0, 200);
            }
        }
    }

    // 4. DIBUJAR PLAZAS (Ajustado para que el coche encaje)
    for (int i = 0; i < NUM_SPOTS; i++) {
        int cX = spots[i].x * TILE_SIZE;
        int cY = spots[i].y * TILE_SIZE + 40; // +40 offset

        // Dimensiones de la plaza
        int w = (TILE_SIZE * 3) + 4;
        int h = TILE_SIZE + 4;

        // Centrar el rectángulo respecto a la coordenada lógica
        int xStart = cX - (TILE_SIZE + 2);
        int yStart = cY - (TILE_SIZE / 2) - 2;

        // PINTAR LÍNEAS "U" (Blanco Brillante)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderDrawLine(renderer, xStart, yStart, xStart + w, yStart); // Arriba
        SDL_RenderDrawLine(renderer, xStart, yStart + h, xStart + w, yStart + h); // Abajo
        SDL_RenderDrawLine(renderer, xStart + w, yStart, xStart + w, yStart + h); // Fondo

        // SENSOR LED
        int pX = cX + TILE_SIZE + 2;
        int pY = cY;

        if (spots[i].isOccupied) {
            draw_box_pixels(pX, pY-3, 6, 6, 255, 0, 0, 255); // Rojo
        } else {
            draw_box_pixels(pX, pY-3, 6, 6, 0, 255, 0, 255); // Verde
        }
    }

    // 5. HUD SUPERIOR (Interfaz)
    draw_box_pixels(0, 0, SCREEN_WIDTH, 40, 30, 30, 30, 255); // Fondo barra
    draw_box_pixels(0, 38, SCREEN_WIDTH, 2, 255, 215, 0, 255); // Línea dorada separadora

    // Simulación de texto (cuadraditos blancos)
    draw_box_pixels(20, 15, 100, 10, 255, 255, 255, 255); // "PARKING"
    draw_box_pixels(SCREEN_WIDTH - 60, 15, 40, 10, 0, 255, 0, 255); // "ONLINE"
}

void draw_car_graphic(int x, int y) {
    // CÁLCULO DE POSICIÓN AJUSTADO
    // Restamos 8 píxeles en Y para subir el coche y centrarlo en la plaza
    int pX = (x - 1) * TILE_SIZE;
    int pY = (y * TILE_SIZE) + 40 - 8;

    // Sombra (para dar profundidad y separar del suelo)
    draw_box_pixels(pX + 4, pY + 4, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 0, 0, 0, 120);

    // Carrocería
    draw_box_pixels(pX + 2, pY + 2, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 255, 200, 0, 255);

    // Detalles del coche
    draw_box_pixels(pX + TILE_SIZE, pY + 5, TILE_SIZE, TILE_SIZE - 10, 50, 100, 200, 255); // Parabrisas
    draw_box_pixels(pX + 2, pY + 4, 4, TILE_SIZE - 8, 255, 255, 200, 255); // Faros
}