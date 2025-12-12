#include <stdio.h>
#include <stdlib.h>
#include "colors.h"


typedef struct {
    int width;
    int height;
    char **grid;
} Map;

void initMap(Map *map) {
    map->grid = (char **)malloc(map->height * sizeof(char *));
    for (int i = 0; i < map->height; i++) {
        map->grid[i] = (char *)malloc(map->width * sizeof(char));
    }

    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            map->grid[i][j] = '.'; // Empty space
        }
    }

    map->grid[0][map->width / 2] = 'E';               // Exit
    map->grid[map->height - 1][map->width / 2] = 'S'; // Entrance

    for (int i = 2; i < map->height - 2; i += 2) {
        for (int j = 2; j < map->width - 2; j += 2) {
            map->grid[i][j] = 'P'; // Parking spot
        }
    }
}

void printMap(Map *map) {
    printf("\nParking Lot:\n");
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            printf("%c ", map->grid[i][j]);
        }
        printf("\n");
    }
}

void addCar(Map *map) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (map->grid[i][j] == 'P') {
                map->grid[i][j] = 'C'; // Car occupies parking spot
                return;
            }
        }
    }
    printf("No empty parking spots available!\n");
}

void freeMap(Map *map) {
    for (int i = 0; i < map->height; i++) {
        free(map->grid[i]);
    }
    free(map->grid);
}

int main() {
    Map parkingLot;
    parkingLot.height = 10; // Example dimensions
    parkingLot.width = 10;

    initMap(&parkingLot);

    char command;
    do {
        printMap(&parkingLot);
        printf("\nCommands:\n");
        printf("T - Add car\n");
        printf("Q - Quit\n");
        printf("Enter command: ");
        scanf(" %c", &command);

        if (command == 'T') {
            addCar(&parkingLot);
        }
    } while (command != 'Q');

    freeMap(&parkingLot);
    return 0;
}