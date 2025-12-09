#include <stdlib.h>
#include <stdio.h>
#include "sound.h"

// Eğer SoX çalışıyorsa:
#define USE_SOX 1

void playSound(const char *filepath) {
    char command[512];

#if USE_SOX
    // SoX ile Windows'ta arka planda ses çalma
    sprintf(command, "start /B sox \"%s\" -t waveaudio", filepath);
#else
    // Alternatif: FFplay ile arka planda çalma (SDL ile çakışmaz)
    sprintf(command, "start /B ffplay -nodisp -autoexit \"%s\"", filepath);
#endif

    printf("PLAY CMD: %s\n", command); // Debug
    system(command);
}

void stopAllSounds() {
#if USE_SOX
    system("taskkill /IM sox.exe /F >nul 2>&1");
#else
    system("taskkill /IM ffplay.exe /F >nul 2>&1");
#endif
}
