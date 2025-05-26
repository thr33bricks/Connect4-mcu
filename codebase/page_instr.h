/**
 * @file page_instr.h
 * @author Yordan Yordanov and Marie-Ange Rousseau
 * @brief Functions for visualizing the instructions page
 * @version 0.1
 * @date 2025-05-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PAGE_INSTR_H
#define PAGE_INSTR_H

#include <stdint.h>

/**
 * @brief Sets the text to start position
 * 
 */
void resetSupLineDisplayed();

/**
 * @brief Displays a few lines on the screen
 * based on an index
 * 
 */
void displayLongText();

/**
 * @brief Calculates the index of the first
 * line to display at the top of the screen
 * 
 */
void greenTextPosition();

/**
 * @brief Displays the scroll on the right
 * of the screen
 * 
 */
void displayScroll();

/**
 * @brief Draws the home button
 * 
 * @param x Pos x
 * @param y Pos y 
 * @param shadow 1 => has shadow, 0 => no shadow
 */
void drawHomeInstr(uint16_t x, uint16_t y, uint8_t shadow);

/**
 * @brief Draws the animation for the home button 
 * 
 * Makes the outline gradually wider
 * 
 */
void drawHomeInstrBtnAnimation();

/**
 * @brief Displays the instructions page
 * 
 */
void displayInstructions();

#endif
