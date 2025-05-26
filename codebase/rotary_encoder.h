#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <stdint.h>

#define ROT_RED   1
#define ROT_GREEN 2
#define ROT_BLUE  3

#define DEBOUNCE_INTERVAL 14


// Initialisation
void initEncoders();

// For buttons
void _checkEdge(uint8_t btn);
uint8_t isDown(uint8_t btn);
uint8_t wasPressed(uint8_t btn);

// For rotations
uint8_t getRotRed();
uint8_t getRotGreen();
uint8_t getRotBlue();
uint8_t getRotDir(uint8_t enc);
void resetRot(uint8_t enc);

#endif