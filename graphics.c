#include "graphics.h"
#include <stdio.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Definimos dónde van las líneas de la carretera
#define LANE_1_X 6
#define LANE_2_X 22
#define LANE_3_X 38

void init_graphics() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) exit(1);
    window = SDL_CreateWindow("Parking Simulator - Final",
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

// Pintar líneas discontinuas
void draw_road_lane(int tileX) {
    int px = tileX * TILE_SIZE;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 180);
    for (int y = 50; y < SCREEN_HEIGHT; y += 40) {
        SDL_Rect dash = { px, y, 4, 20 };
        SDL_RenderFillRect(renderer, &dash);
    }
}

// Texto simple
void draw_char(char c, int x, int y, int size) {
    int s[5] = {0};
    if (c=='P') { s[0]=30; s[1]=17; s[2]=30; s[3]=16; s[4]=16; }
    else if (c=='R') { s[0]=30; s[1]=17; s[2]=30; s[3]=20; s[4]=18; }
    else if (c=='E') { s[0]=31; s[1]=16; s[2]=30; s[3]=16; s[4]=31; }
    else if (c=='S') { s[0]=15; s[1]=16; s[2]=14; s[3]=1; s[4]=30; }
    else if (c=='1') { s[0]=4; s[1]=12; s[2]=4; s[3]=4; s[4]=14; }
    else if (c=='T') { s[0]=31; s[1]=4; s[2]=4; s[3]=4; s[4]=4; }
    else if (c=='O') { s[0]=14; s[1]=17; s[2]=17; s[3]=17; s[4]=14; }
    else if (c=='A') { s[0]=14; s[1]=17; s[2]=31; s[3]=17; s[4]=17; }
    else if (c=='D') { s[0]=30; s[1]=17; s[2]=17; s[3]=17; s[4]=30; }
    else if (c=='N') { s[0]=17; s[1]=25; s[2]=21; s[3]=19; s[4]=17; }
    else if (c=='W') { s[0]=17; s[1]=17; s[2]=21; s[3]=21; s[4]=10; }
    else if (c=='C') { s[0]=14; s[1]=16; s[2]=16; s[3]=16; s[4]=14; }
    else if (c=='I') { s[0]=14; s[1]=4; s[2]=4; s[3]=4; s[4]=14; }
    else if (c=='X') { s[0]=17; s[1]=10; s[2]=4; s[3]=10; s[4]=17; }
    else if (c=='B') { s[0]=30; s[1]=17; s[2]=30; s[3]=17; s[4]=30; }
    else if (c=='U') { s[0]=17; s[1]=17; s[2]=17; s[3]=17; s[4]=14; }
    else if (c=='Y') { s[0]=17; s[1]=10; s[2]=4; s[3]=4; s[4]=4; }
    else if (c=='M') { s[0]=17; s[1]=27; s[2]=21; s[3]=17; s[4]=17; }
    else if (c=='2') { s[0]=14; s[1]=1; s[2]=14; s[3]=16; s[4]=30; }
    else if (c=='F') { s[0]=31; s[1]=16; s[2]=30; s[3]=16; s[4]=16; }
    else if (c=='V') { s[0]=17; s[1]=17; s[2]=17; s[3]=10; s[4]=4; }



    else if (c==' ') { }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int r=0; r<5; r++) {
        for(int col=0; col<5; col++) {
            if((s[r] >> (4-col)) & 1) {
                SDL_Rect p = {x + (col*size), y + (r*size), size, size};
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
    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderClear(renderer);
    draw_string("PRESS 1 TO START IN EASY MODE", (SCREEN_WIDTH/2)-140, SCREEN_HEIGHT/2, 3);
    draw_string("PRESS 2 TO START IN BUSY MODE", (SCREEN_WIDTH/2)-140, (SCREEN_HEIGHT/2)+30, 3);

}

void draw_background() {
    // HUD
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_box_pixels(0, 0, SCREEN_WIDTH, 50, 25, 25, 25, 255);
    draw_string("SPACE NEW", 20, 15, 2);
    draw_string("D REMOVE CAR", 250, 15, 2);
    draw_string("M FOR MENU", 500, 15, 2);




    int offY = 50;

    // SUELO ASFALTO
    draw_box_pixels(0, offY, SCREEN_WIDTH, SCREEN_HEIGHT, 50, 50, 55, 255);

    // LÍNEAS DE CARRETERA
    draw_road_lane(LANE_1_X);
    draw_road_lane(LANE_2_X);
    draw_road_lane(LANE_3_X);

    // MAPA
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            char cell = asciiMap[y][x];
            int pX = x * TILE_SIZE;
            int pY = (y * TILE_SIZE) + offY;

            if (cell == '#') {
                draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 139, 69, 19, 255);
                SDL_SetRenderDrawColor(renderer, 0,0,0,255);
                SDL_Rect border = {pX, pY, TILE_SIZE, TILE_SIZE};
                SDL_RenderDrawRect(renderer, &border);
            }
            else if (cell == 'E') draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 0, 100, 0, 100);
            else if (cell == 'X') draw_box_pixels(pX, pY, TILE_SIZE, TILE_SIZE, 100, 0, 0, 100);
        }
    }

    // PLAZAS
    for (int i = 0; i < NUM_SPOTS; i++) {
        int cX = spots[i].x * TILE_SIZE;
        int cY = (spots[i].y * TILE_SIZE) + offY;

        int w = (TILE_SIZE * 3) + 4;
        int h = TILE_SIZE + 4;
        int xStart = cX - (TILE_SIZE + 2);
        int yStart = cY - (TILE_SIZE / 2) - 2;
        int thick = 3;

        draw_box_pixels(xStart, yStart, w, thick, 255, 255, 255, 255);
        draw_box_pixels(xStart, yStart + h, w, thick, 255, 255, 255, 255);
        draw_box_pixels(xStart + w, yStart, thick, h + thick, 255, 255, 255, 255);

        int pX = cX + TILE_SIZE + 4; int pY = yStart - 10;
        draw_box_pixels(pX-2, pY-2, 10, 10, 20, 20, 20, 255);
        if (spots[i].isOccupied) draw_box_pixels(pX, pY, 6, 6, 255, 0, 0, 255);
        else draw_box_pixels(pX, pY, 6, 6, 0, 255, 0, 255);
    }
}

// ESTA ES LA FUNCIÓN QUE FALTABA Y ROMPÍA LA COMPILACIÓN
void draw_car_smooth(float x, float y) {
    int pX = (int)(x * TILE_SIZE) - TILE_SIZE;
    int pY = (int)(y * TILE_SIZE) + 50 - 8;

    // Sombra
    draw_box_pixels(pX + 4, pY + 4, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 0, 0, 0, 100);
    // Carrocería
    draw_box_pixels(pX + 2, pY + 2, (3 * TILE_SIZE) - 4, TILE_SIZE - 4, 255, 215, 0, 255);
    // Cristal
    draw_box_pixels(pX + TILE_SIZE, pY + 5, TILE_SIZE, TILE_SIZE - 10, 50, 100, 200, 255);
}

// Mantenemos esta por si acaso, aunque no se use
void draw_car_graphic(int x, int y) {
    draw_car_smooth((float)x, (float)y);
}