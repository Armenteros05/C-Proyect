#ifndef SOUND_H
#define SOUND_H

void playSound(const char *filepath);   // Tek seferlik ses
void playLooped(const char *filepath);  // Sonsuz döngü motor sesi
void stopAllSounds();                   // Tüm sesleri kapat

#endif
