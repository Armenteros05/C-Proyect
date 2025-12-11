#include <stdlib.h>
#include <stdio.h>
#include "sound.h"

#define SOX_PATH "bin\\sox.exe"

void playSound(const char *filepath) {
    char command[512];

    sprintf(command,
        "start \"\" /B /MIN \"%s\" \"%s\" -t waveaudio",
        SOX_PATH, filepath);

    system(command);
}

void playLooped(const char *filepath) {
    char command[512];

    sprintf(command,
        "start \"\" /B /MIN \"%s\" \"%s\" -t waveaudio repeat 999999",
        SOX_PATH, filepath);

    system(command);
}

void stopAllSounds() {
    system("taskkill /IM sox.exe /F >nul 2>&1");
}
