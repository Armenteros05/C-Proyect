#include <windows.h>
#include <stdio.h>
#include "map.h"

int main() {
    initMap();

    while (1) {
        printMap();
        Sleep(100);  // Sleep in ms, works on Windows
    }

    return 0;
}
