#include <stdio.h>
#include <string.h>
#include "map.h"

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

char parkingMap[MAP_ROWS][MAP_COLS + 1];

void resetMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        strncpy(parkingMap[i], asciiMap[i], MAP_COLS);
        parkingMap[i][MAP_COLS] = '\0';
    }
}

void printMap() {
    for (int i = 0; i < MAP_ROWS; i++) {
        printf("%s\n", parkingMap[i]);
    }
}
