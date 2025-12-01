#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "map.h"
#include "vehicle.h"

// Configuración de la Ventana
#define TILE_SIZE 24        // Tamaño de cada cuadrado (24x24 pixeles)
#define SCREEN_WIDTH  (MAP_COLS * TILE_SIZE)
#define SCREEN_HEIGHT (MAP_ROWS * TILE_SIZE)

// Funciones
void init_graphics();
void close_graphics();
void draw_background(); // Dibuja mapa y plazas
void draw_car_graphic(int x, int y); // Dibuja un coche

// Variable global del renderizador para uso interno
extern SDL_Renderer* renderer;

#endif