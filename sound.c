#include <stdio.h>
#include <stdlib.h>
#include "sound.h"

#ifdef _WIN32
#define SOX_OUTPUT "-t waveaudio"
#else
#define SOX_OUTPUT "-d"
#endif


#ifdef _WIN32
#define SOX_CMD "bin\\sox.exe"
#else
#define SOX_CMD "./bin/sox"
#endif

void playSound(const char *filepath) {
    char command[512];

#ifdef _WIN32
    // Windows: waveaudio kullan
    sprintf(command, "start /B \"\" %s \"%s\" -t waveaudio >NUL 2>&1",
            SOX_CMD, filepath);
#else
    // Linux
    sprintf(command, "%s \"%s\" -d >/dev/null 2>&1 &",
            SOX_CMD, filepath);
#endif

    system(command);
}

void playLooped(const char *filepath) {
    char command[512];

#ifdef _WIN32
    sprintf(command, "start /B \"\" %s \"%s\" -t waveaudio repeat 999999 >NUL 2>&1",
            SOX_CMD, filepath);
#else
    sprintf(command, "%s \"%s\" -d repeat 999999 >/dev/null 2>&1 &",
            SOX_CMD, filepath);
#endif

    system(command);
}

void stopAllSounds() {
#ifdef _WIN32
    system("taskkill /IM sox.exe /F >NUL 2>&1");
#else
    system("pkill sox >/dev/null 2>&1");
#endif
}
