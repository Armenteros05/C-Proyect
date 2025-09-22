#include <stdio.h>
#include <stdlib.h>

// Define a Map structure
typedef struct {
    int width;
    int height;
    char **grid;  // dynamically allocated 2D array
} Map;

// Function to initialize the map
void initMap(Map *map) {
    map->grid = (char **)malloc(map->height * sizeof(char *));
    for (int i = 0; i < map->height; i++) {
        map->grid[i] = (char *)malloc(map->width * sizeof(char));
    }

    // Fill map with empty spaces
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            map->grid[i][j] = '.';  // road/empty
        }
    }

    // Add entrance and exit
    map->grid[0][map->width / 2] = 'E';               // Exit
    map->grid[map->height - 1][map->width / 2] = 'S'; // Start/Enter

    // Example: Add parking spots
    for (int i = 2; i < map->height - 2; i += 2) {
        for (int j = 2; j < map->width - 2; j += 2) {
            map->grid[i][j] = 'P'; // Parking spot
        }
    }
}

// Function to print the map compactly
void printMap(Map *map) {
    // Top border
    printf(" ");
    for (int j = 0; j < map->width * 2; j++) {
        printf("-");
    }
    printf("\n");

    // Rows
    for (int i = 0; i < map->height; i++) {
        printf("|"); // Left border
        for (int j = 0; j < map->width; j++) {
            if (map->grid[i][j] == 'P') {
                printf("[]");   // parking spot
            } else if (map->grid[i][j] == 'E') {
                printf("EXIT");
                j += 1; // skip extra cell (EXIT uses 4 chars)
            } else if (map->grid[i][j] == 'S') {
                printf("ENTR");
                j += 1; // skip extra cell (ENTR uses 4 chars)
            } else {
                printf("  ");   // empty road
            }
        }
        printf("|\n"); // Right border
    }

    // Bottom border
    printf(" ");
    for (int j = 0; j < map->width * 2; j++) {
        printf("-");
    }
    printf("\n");
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

    fscanf(file, "%*[^:] : %d", &parkingLot.height); // Read Length
    fscanf(file, "%*[^:] : %d", &parkingLot.width);  // Read Width
    fclose(file);

    initMap(&parkingLot);
    printMap(&parkingLot);
    freeMap(&parkingLot);

    return 0;
}
