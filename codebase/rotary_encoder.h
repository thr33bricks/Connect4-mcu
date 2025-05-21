#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#define REVERSE

void *knobsBase;

// Initialisation
void initEncoders();

// For buttons
uint8_t isRedClicked();
uint8_t isGreenClicked();
uint8_t isBlueClicked();
// int clicked();

// For rotations
uint8_t getRotRed();
uint8_t getRotGreen();
uint8_t getRotBlue();

#endif