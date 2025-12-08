#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "map.h"
#include "vehicle.h"

#define TILE_SIZE 24
#define SCREEN_WIDTH  (MAP_COLS * TILE_SIZE)
#define SCREEN_HEIGHT (MAP_ROWS * TILE_SIZE)

void init_graphics();
void close_graphics();
void draw_background();
void draw_menu_screen();
// CAMBIO IMPORTANTE: float para suavidad
void draw_car_smooth(float x, float y);

extern SDL_Renderer* renderer;

#endif