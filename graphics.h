#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "map.h"
#include "vehicle.h"

// Altura extra para la barra de interfaz
#define TILE_SIZE 24
#define SCREEN_WIDTH  (MAP_COLS * TILE_SIZE)
#define SCREEN_HEIGHT (MAP_ROWS * TILE_SIZE)

// Funciones
void init_graphics();
void close_graphics();
void draw_background();
void draw_menu_screen(); // <--- NUEVA
void draw_car_graphic(int x, int y);

extern SDL_Renderer* renderer;

#endif