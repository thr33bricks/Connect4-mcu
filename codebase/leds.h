/**
 * @file leds.h
 * @author Yordan Yordanov and Marie-Ange Rousseau
 * @brief A library for controlling the 2 RGB leds and
 * the 32 led line
 * @version 0.1
 * @date 2025-05-26
 * 
 * @copyright Copyright (c) 2025
 *            license: GNU General Public License v3.0 * 
 */

#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

/**
 * @brief Maps memory and turns off RGB leds
 * 
 */
void initLeds();

/**
 * @brief Sets RGB led 1
 * 
 * @param color RGB888-coded colour
 */
void setLed1(uint32_t color);

/**
 * @brief Sets RGB led 2
 * 
 * @param color RGB888-coded colour
 */
void setLed2(uint32_t color);

/**
 * @brief Sets the 32 leds line
 * 
 * @param state Each bit represents an led (32 bits)
 */
void setLedsLine(uint32_t state);

/**
 * @brief Sets the 2 RGB leds to yellow or red
 * 
 * currentPlayer => 0 for yellow, 1 for red
 * 
 * @param current_player 
 */
void setPlayerLed(uint8_t current_player);

/**
 * @brief Turns the 2 RGB leds off
 * 
 */
void setPlayerLedOff();

/**
 * @brief Plays animation on the 32 led
 * 
 * Used for game over
 * 
 */
void gameOverLEDS();

#endif
