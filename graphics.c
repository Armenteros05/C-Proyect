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
                              SCREEN_WIDTH, SCREEN_HEIGHT + 50, SDL_WINDOW_SHOWN);
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

void draw_char(char c, int x, int y, int size) {
    // Definición básica de letras
    int shapes[5] = {0,0,0,0,0};
    // Alfabeto mínimo necesario
    if (c=='E') { shapes[0]=31; shapes[1]=16; shapes[2]=30; shapes[3]=16; shapes[4]=31; }
    else if (c=='N') { shapes[0]=17; shapes[1]=25; shapes[2]=21; shapes[3]=19; shapes[4]=17; }
    else if (c=='T') { shapes[0]=31; shapes[1]=4; shapes[2]=4; shapes[3]=4; shapes[4]=4; }
    else if (c=='R') { shapes[0]=30; shapes[1]=17; shapes[2]=30; shapes[3]=20; shapes[4]=18; }
    else if (c=='Y') { shapes[0]=17; shapes[1]=17; shapes[2]=10; shapes[3]=4; shapes[4]=4; }
    else if (c=='X') { shapes[0]=17; shapes[1]=10; shapes[2]=4; shapes[3]=10; shapes[4]=17; }
    else if (c=='I') { shapes[0]=14; shapes[1]=4; shapes[2]=4; shapes[3]=4; shapes[4]=14; }
    // ... (El resto se mantienen igual que la versión anterior)

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

void draw_string(const char* str, int x, int y, int size) {
    int cursor = x;
    while (*str) {
        draw_char(*str, cursor, y, size);
        cursor += (6 * size);
        str++;
    }
}

void draw_menu_screen() {
    SDL_SetRenderDrawColor(renderer, 20, 30, 50, 255);
    SDL_RenderClear(renderer);
    draw_string("PRESS 1 TO START", (SCREEN_WIDTH/2)-140, SCREEN_HEIGHT/2, 3);
}

void draw_background() {
    // HUD
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_box_pixels(0, 0, SCREEN_WIDTH, 50, 30, 30, 30, 255);

    // Instrucciones HUD
    draw_string("SPACE NEW", 20, 15, 2);
    draw_string("D EXIT", 300, 15, 2);
    draw_box_pixels(0, 48, SCREEN_WIDTH, 2, 255, 215, 0, 255);

    int offsetY = 50;

    // Suelo
    draw_box_pixels(0, offsetY, SCREEN_WIDTH, SCREEN_HEIGHT, 45, 45, 50, 255);

    // Muros, Garitas y Plazas
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
            else if (cell == 'G') {
                // GARITA (Caseta azulada con ventana)
                draw_box_pixels(pX, pY, TILE_SIZE*2, TILE_SIZE*2, 60, 80, 100, 255); // Estructura
                draw_box_pixels(pX+5, pY+10, (TILE_SIZE*2)-10, TILE_SIZE, 150, 200, 255, 255); // Ventana
                draw_box_pixels(pX-2, pY-5, (TILE_SIZE*2)+4, 5, 40, 40, 40, 255); // Techo

                // Texto ENTRY o EXIT
                if (y < 10) draw_string("ENTRY", pX, pY-20, 2); // Arriba
                else draw_string("EXIT", pX, pY-20, 2); // Abajo
            }
        }
    }

    // Plazas (Igual que antes)
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

        // Sensor
        int pX = cX + TILE_SIZE + 2; int pY = yStart - 10;
        draw_box_pixels(pX-2, pY-2, 10, 10, 20, 20, 20, 255);
        if (spots[i].isOccupied) draw_box_pixels(pX, pY, 6, 6, 255, 0, 0, 255);
        else draw_box_pixels(pX, pY, 6, 6, 0, 255, 0, 255);
    }
}

void draw_car_smooth(float x, float y) {
    int pX = (int)(x * TILE_SIZE) - TILE_SIZE;
    int pY = (int)(y * TILE_SIZE) + 50 - 8;

    draw_box_pixels(pX + 4, pY + 4, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 0, 0, 0, 100);
    draw_box_pixels(pX + 2, pY + 2, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 255, 200, 0, 255);
    draw_box_pixels(pX + TILE_SIZE, pY + 5, TILE_SIZE, TILE_SIZE - 10, 50, 100, 200, 255);
}