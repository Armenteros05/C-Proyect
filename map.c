#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a Map structure
typedef struct {
    int width;
    int height;
    char **grid;
    int carX, carY; // Car's position
} Map;

// Initialize the map
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

    // Define multiple parking spots
    for (int i = 2; i < map->height - 2; i += 2) {
        for (int j = 2; j < map->width - 2; j += 4) {
            map->grid[i][j] = 'P'; // Parking spot
        }
    }
}

// Print the map with textures
void printMap(Map *map) {
    printf("\n ");
    for (int j = 0; j < map->width * 2; j++) {
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < map->height; i++) {
        printf("|");
        for (int j = 0; j < map->width; j++) {
            if (map->grid[i][j] == 'P') {
                printf("[]"); // Parking spot
            } else if (map->grid[i][j] == 'E') {
                printf("EXIT");
                j += 1;
            } else if (map->grid[i][j] == 'S') {
                printf("ENTR");
                j += 1;
            } else if (map->grid[i][j] == 'O') {
                printf(" O"); // Car
            } else {
                printf("  "); // Empty space
            }
        }
        printf("|\n");
    }

    printf(" ");
    for (int j = 0; j < map->width * 2; j++) {
        printf("-");
    }
    printf("\n");
}

// Search for the next empty parking spot
bool findParkingSpot(Map *map, int *targetX, int *targetY) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (map->grid[i][j] == 'P') {
                *targetX = i;
                *targetY = j;
                return true;
            }
        }
    }
    return false; // No available spots
}

// Move the car automatically to the parking spot
void moveCarToSpot(Map *map) {
    int targetX, targetY;
    if (!findParkingSpot(map, &targetX, &targetY)) {
        printf("No parking spots available!\n");
        return;
    }

    while (map->carX != targetX || map->carY != targetY) {
        int newX = map->carX;
        int newY = map->carY;

        if (map->carX < targetX) newX++;        // Move down
        else if (map->carX > targetX) newX--;   // Move up

        if (map->carY < targetY) newY++;        // Move right
        else if (map->carY > targetY) newY--;   // Move left

        // Validate movement
        if (newX >= 0 && newX < map->height && newY >= 0 && newY < map->width && map->grid[newX][newY] != 'O') {
            map->grid[map->carX][map->carY] = '.'; // Clear old position
            map->carX = newX;
            map->carY = newY;
            map->grid[map->carX][map->carY] = 'O'; // Update new position
            printMap(map);
        }
    }

    // Park the car
    map->grid[targetX][targetY] = 'O';
    printf("Car parked at (%d, %d)\n", targetX, targetY);
}

// Add a new car at the entrance
bool addNewCar(Map *map) {
    int entranceX = map->height - 1;
    int entranceY = map->width / 2;

    if (map->grid[entranceX][entranceY] == '.') {
        map->carX = entranceX;
        map->carY = entranceY;
        map->grid[map->carX][map->carY] = 'O'; // Place the car at the entrance
        return true;
    } else {
        printf("Entrance is blocked! No more cars can enter.\n");
        return false;
    }
}

// Free memory
void freeMap(Map *map) {
    for (int i = 0; i < map->height; i++) {
        free(map->grid[i]);
    }
    free(map->grid);
}

int main() {
    Map parkingLot;
    FILE *file = fopen("map.txt", "r");
    if (!file) {
        printf("Error: Could not open map.txt\n");
        return 1;
    }

    fscanf(file, "%*[^:] : %d", &parkingLot.height);
    fscanf(file, "%*[^:] : %d", &parkingLot.width);
    fclose(file);

    initMap(&parkingLot);

    char command;
    while (true) {
        printMap(&parkingLot);
        printf("\nCommands:\n");
        printf("T - Issue parking ticket\n");
        printf("Q - Quit\n");
        printf("Enter command: ");
        scanf(" %c", &command);

        if (command == 'T') {
            if (addNewCar(&parkingLot)) {
                moveCarToSpot(&parkingLot);
            } else {
                printf("Entrance is blocked! No more cars can enter.\n");
            }
        } else if (command == 'Q') {
            break;
        }
    }

    freeMap(&parkingLot);
    return 0;
}m.ñ<<