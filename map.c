#include <stdio.h>
#include <string.h>
#include "map.h"

// Original ASCII map
const char *asciiMap[MAP_ROWS] = {
        "+---------------------------------------------------------------------------------+",
        "| ENTER                                                                           |",
        "| HERE                                                                            |",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|I                    II                   II                   II               I|",
        "|I                    II                   II                   II               I|",
        "|-----            ----++----           ----++----           ----++----       -----|",
        "|                                                                            EXIT |",
        "|                                                                            HERE |",
        "|---------------------------------------------------------------------------------|"
};

// The working parking map where vehicles are drawn
char parkingMap[MAP_ROWS][MAP_COLS + 1];

// Reset the parking map to the original ASCII map
void resetMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        strncpy(parkingMap[i], asciiMap[i], MAP_COLS);
        parkingMap[i][MAP_COLS] = '\0';
    }
}

// Print the current parking map
void printMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        printf("%s\n", parkingMap[i]);
    }
}
