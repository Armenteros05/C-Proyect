#include "graphics.h"
#include <stdio.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

#define ROAD_1_X 6
#define ROAD_2_X 24
#define ROAD_3_X 40

void init_graphics() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) exit(1);
    window = SDL_CreateWindow("ESIEA Parking Simulator - Final",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT + 50, SDL_WINDOW_SHOWN); // +50px para HUD
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

// --- SISTEMA DE TEXTO SIMPLE (Pixel Art) ---
// Dibuja letras predefinidas 5x7 pixels
void draw_char(char c, int x, int y, int size) {
    // Definición muy básica de letras (1 = pixel pintado)
    // Esto es un "hack" para no instalar librerías de fuentes
    int shapes[5] = {0,0,0,0,0};

    if (c == '1') { shapes[0]=4; shapes[1]=12; shapes[2]=4; shapes[3]=4; shapes[4]=14; }
    else if (c == 'P') { shapes[0]=30; shapes[1]=17; shapes[2]=30; shapes[3]=16; shapes[4]=16; }
    else if (c == 'R') { shapes[0]=30; shapes[1]=17; shapes[2]=30; shapes[3]=20; shapes[4]=18; }
    else if (c == 'E') { shapes[0]=31; shapes[1]=16; shapes[2]=30; shapes[3]=16; shapes[4]=31; }
    else if (c == 'S') { shapes[0]=15; shapes[1]=16; shapes[2]=14; shapes[3]=1; shapes[4]=30; }
    else if (c == 'T') { shapes[0]=31; shapes[1]=4; shapes[2]=4; shapes[3]=4; shapes[4]=4; }
    else if (c == 'O') { shapes[0]=14; shapes[1]=17; shapes[2]=17; shapes[3]=17; shapes[4]=14; }
    else if (c == 'A') { shapes[0]=14; shapes[1]=17; shapes[2]=31; shapes[3]=17; shapes[4]=17; }
    else if (c == 'L') { shapes[0]=16; shapes[1]=16; shapes[2]=16; shapes[3]=16; shapes[4]=31; }
    else if (c == 'D') { shapes[0]=30; shapes[1]=17; shapes[2]=17; shapes[3]=17; shapes[4]=30; }
    else if (c == 'N') { shapes[0]=17; shapes[1]=25; shapes[2]=21; shapes[3]=19; shapes[4]=17; }
    else if (c == 'W') { shapes[0]=17; shapes[1]=17; shapes[2]=21; shapes[3]=21; shapes[4]=10; }
    else if (c == 'C') { shapes[0]=14; shapes[1]=16; shapes[2]=16; shapes[3]=16; shapes[4]=14; }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int row=0; row<5; row++) {
        int val = shapes[row];
        for(int col=0; col<5; col++) {
            if((val >> (4-col)) & 1) {
                SDL_Rect p = {x + (col*size), y + (row*size), size, size};
                SDL_RenderFillRect(renderer, &p);
            }
        }
    }
}

// Función auxiliar para escribir palabras soportadas
void draw_string(const char* str, int x, int y, int size) {
    int cursor = x;
    while (*str) {
        draw_char(*str, cursor, y, size);
        cursor += (6 * size); // Espacio entre letras
        str++;
    }
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

// --- MENÚ PRINCIPAL ---
void draw_menu_screen() {
    SDL_SetRenderDrawColor(renderer, 20, 30, 50, 255); // Azul oscuro
    SDL_RenderClear(renderer);

    // Título simulado (Bloques)
    draw_box_pixels(SCREEN_WIDTH/2 - 100, 100, 200, 10, 255, 215, 0, 255);

    // Usamos nuestra función de texto para "PRESS 1 TO START"
    // Nota: Solo he definido algunas letras arriba, así que usaré bloques si faltan
    // O mejor, dibujamos el texto clave: "PRESS 1"

    int cx = (SCREEN_WIDTH / 2) - 150;
    int cy = (SCREEN_HEIGHT / 2);

    draw_string("PRESS", cx, cy, 4);      // x, y, tamaño
    draw_string("1", cx + 150, cy, 4);
    draw_string("TO", cx + 200, cy, 4);
    draw_string("START", cx + 280, cy, 4);

    // Decoración
    draw_box_pixels(cx, cy + 50, 400, 2, 255, 255, 255, 100);
}

void draw_background() {
    // 1. HUD SUPERIOR (Barra negra con instrucciones)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_box_pixels(0, 0, SCREEN_WIDTH, 50, 20, 20, 20, 255); // Fondo HUD

    // Texto del HUD (Simulado o letras)
    // "[SPACE] NEW CAR"
    draw_string("SPACE", 20, 15, 2);
    draw_string("NEW", 100, 15, 2);
    draw_string("CAR", 150, 15, 2);

    // "[D] DEPART"
    draw_string("D", 300, 15, 2);
    draw_string("TO", 330, 15, 2);
    draw_string("EXIT", 360, 15, 2);

    // Separador
    draw_box_pixels(0, 48, SCREEN_WIDTH, 2, 255, 215, 0, 255); // Línea dorada

    // 2. JUEGO (Desplazado +50px hacia abajo)
    int offsetY = 50;

    // Asfalto
    draw_box_pixels(0, offsetY, SCREEN_WIDTH, SCREEN_HEIGHT, 45, 45, 50, 255);

    // Carriles
    int px1 = ROAD_1_X * TILE_SIZE;
    int px2 = ROAD_2_X * TILE_SIZE;
    int px3 = ROAD_3_X * TILE_SIZE;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
    for (int y = offsetY; y < SCREEN_HEIGHT+offsetY; y += 40) {
        if (y > (4 * TILE_SIZE)+offsetY) {
            SDL_Rect d1 = { px1, y, 4, 20 }; SDL_RenderFillRect(renderer, &d1);
            SDL_Rect d2 = { px2, y, 4, 20 }; SDL_RenderFillRect(renderer, &d2);
            SDL_Rect d3 = { px3, y, 4, 20 }; SDL_RenderFillRect(renderer, &d3);
        }
    }

    // Muros y Plazas
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            char cell = asciiMap[y][x];
            int pX = x * TILE_SIZE;
            int pY = (y * TILE_SIZE) + offsetY;

            if (cell == '#') {
                draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 139, 69, 19, 255);
                SDL_SetRenderDrawColor(renderer, 0,0,0,255);
                SDL_Rect b = {pX, pY, TILE_SIZE, TILE_SIZE};
                SDL_RenderDrawRect(renderer, &b);
            }
            else if (cell == 'X') { // SALIDA
                draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 50, 0, 0, 150); // Rojo oscuro suelo
            }
        }
    }

    // Plazas
    for (int i = 0; i < NUM_SPOTS; i++) {
        int cX = spots[i].x * TILE_SIZE;
        int cY = (spots[i].y * TILE_SIZE) + offsetY;

        int w = (TILE_SIZE * 3) + 4;
        int h = TILE_SIZE + 4;
        int xStart = cX - (TILE_SIZE + 2);
        int yStart = cY - (TILE_SIZE / 2) - 2;

        int thick = 3;
        draw_box_pixels(xStart, yStart, w, thick, 255, 255, 255, 255);
        draw_box_pixels(xStart, yStart + h, w, thick, 255, 255, 255, 255);
        draw_box_pixels(xStart + w, yStart, thick, h + thick, 255, 255, 255, 255);

        int pX = cX + TILE_SIZE + 2;
        int pY = yStart - 10;

        // Base piloto
        draw_box_pixels(pX-2, pY-2, 10, 10, 20, 20, 20, 255);
        if (spots[i].isOccupied) draw_box_pixels(pX, pY, 6, 6, 255, 0, 0, 255);
        else draw_box_pixels(pX, pY, 6, 6, 0, 255, 0, 255);
    }
}

void draw_car_smooth(float x, float y) {
    int pX = (int)(x * TILE_SIZE) - TILE_SIZE;
    int pY = (int)(y * TILE_SIZE) + 50 - 8; // +50 HUD offset

    draw_box_pixels(pX + 4, pY + 4, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 0, 0, 0, 100);
    draw_box_pixels(pX + 2, pY + 2, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 255, 200, 0, 255);
    draw_box_pixels(pX + TILE_SIZE, pY + 5, TILE_SIZE, TILE_SIZE - 10, 50, 100, 200, 255);
}