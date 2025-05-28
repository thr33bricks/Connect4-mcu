/**
 * @file rotary_encoder.h
 * @author Yordan Yordanov and Marie-Ange Rousseau
 * @brief A library that makes reading and using 
 * the rotary encoders and buttons extremely easy
 * @version 0.1
 * @date 2025-05-27
 * 
 * @copyright Copyright (c) 2025
 *            license: GNU General Public License v3.0
 * 
 */

#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <stdint.h>

// Which knob/button
#define ROT_RED   1
#define ROT_GREEN 2
#define ROT_BLUE  3

// Minimal time between readings
#define DEBOUNCE_INTERVAL 14


/**
 * @brief Memory map and setting vars
 * to zero
 * 
 */
void initEncoders();

/**
 * @brief Saves the reading by comparing 
 * values taken before and after an interval. 
 * After that it compares current reading and
 * last reading and decides if it was falling
 * edge. If that is the case the button was
 * pressed.
 * 
 * @param btn Which button
 */
void checkEdge(uint8_t btn);

/**
 * @brief Checks if button is down
 * 
 * @param btn which button
 * @return uint8_t 1 => down, 0 => up
 */
uint8_t isDown(uint8_t btn);

/**
 * @brief Checks if button
 * was pressed
 * 
 * @param btn which button
 * @return uint8_t 1 => pressed, 0 => not 
 * pressed
 */
uint8_t wasPressed(uint8_t btn);

/**
 * @brief Get the rotations value 
 * of the red rotary encoder
 * 
 * @return uint8_t value 0-63
 */
uint8_t getRotRed();

/**
 * @brief Get the rotations value 
 * of the green rotary encoder
 * 
 * @return uint8_t value 0-63
 */
uint8_t getRotGreen();

/**
 * @brief Get the rotations value 
 * of the blue rotary encoder
 * 
 * @return uint8_t value 0-63
 */
uint8_t getRotBlue();

/**
 * @brief Get the rotary encoder 
 * rotation value
 * 
 * @param enc which encoder
 * @return uint8_t 'l', 'r', 0
 */
uint8_t getRotDir(uint8_t enc);

/**
 * @brief Resets rotation
 * 
 * @param enc which encoder
 */
void resetRot(uint8_t enc);

#endif