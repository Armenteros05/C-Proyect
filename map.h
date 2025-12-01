#ifndef MAP_H
#define MAP_H

#define MAP_ROWS 24
#define MAP_COLS 65 // Ancho ajustado para 3 columnas de parking y 2 carreteras
#define NUM_SPOTS 18 // 6 plazas por columna x 3 columnas

// Códigos de color ANSI para Linux/Unix
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct {
    int x;       // Centro X donde se dibuja el coche
    int y;       // Fila Y
    int isOccupied;
    // Límites visuales para pintar la caja de color
    int x_min, x_max, y_min, y_max;
} ParkingSpot;

extern char parkingMap[MAP_ROWS][MAP_COLS + 1];
extern const char *asciiMap[MAP_ROWS];
extern ParkingSpot spots[NUM_SPOTS];

void resetMap();
void printMap();
int findFreeSpot();
void occupySpot(int spotIndex);

#endif