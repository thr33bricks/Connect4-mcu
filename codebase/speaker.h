#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>

void initSpeaker();
void playTone(uint32_t frequency, uint32_t duration_ms);

#endif // SPEAKER_H
