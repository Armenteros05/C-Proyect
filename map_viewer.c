

#include <stdio.h>
#include "map.h"
#include "colors.h"


#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int main() {
    initMap();

    while (1) {
        printMap();

#ifdef _WIN32
        Sleep(100);            // Windows: ms
#else
        usleep(100 * 1000);    // Linux: microseconds
#endif
    }

    return 0;
}

