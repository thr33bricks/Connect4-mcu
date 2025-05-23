#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

void initLeds();
void setLed1(uint32_t color);
void setLed2(uint32_t color);
void setLedsLine(uint32_t state);

void setPlayerLed(uint8_t current_player);
void gameOverLEDS();

#endif // LEDS_H
