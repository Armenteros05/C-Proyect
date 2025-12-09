#include <stdlib.h>
#include <stdio.h>
#include "sound.h"

// Eğer SoX çalışıyorsa:
#define USE_SOX 1

void playSound(const char *filepath) {
    char command[512];

#if USE_SOX
    sprintf(command, "start /B sox \"%s\" -t waveaudio", filepath);
#else
    sprintf(command, "start /B ffplay -nodisp -autoexit \"%s\"", filepath);
#endif

    printf("PLAY CMD: %s\n", command);
    system(command);
}

// -------------------------------------
//   MOTOR SESİ İÇİN LOOP FONKSİYONU
// -------------------------------------
void playLooped(const char *filepath) {
    char command[512];

    printf("MOTOR SESI ÇALIŞTIRILIYOR: %s\n", filepath); // DEBUG BURADA

#if USE_SOX
    // Sonsuz döngü yerine büyük bir sayı kullanıyoruz
    sprintf(command, "start /B sox \"%s\" -t waveaudio repeat 999999", filepath);
#else
    sprintf(command, "start /B ffplay -nodisp -autoexit -loop 0 \"%s\"", filepath);
#endif

    system(command);
}


void stopAllSounds() {
#if USE_SOX
    system("taskkill /IM sox.exe /F >nul 2>&1");
#else
    system("taskkill /IM ffplay.exe /F >nul 2>&1");
#endif
}
