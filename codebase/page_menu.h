/**
 * @file page_menu.h
 * @author Yordan Yordanov and Marie-Ange Rousseau
 * @brief 
 * @version 0.1
 * @date 2025-05-26
 * 
 * @copyright Copyright (c) 2025
 *            license: GNU General Public License v3.0
 * 
 */

#ifndef PAGE_MENU_H
#define PAGE_MENU_H

#include <stdint.h>

/**
 * @brief Draws the Connect 4 title
 * 
 */
void drawConnect4Title();

/**
 * @brief Draws the play button
 * 
 * @param x The pos x of the top left corner
 * @param y The pos y of the top left corner
 */
void drawPlayButton(uint16_t x, uint16_t y);

/**
 * @brief Draws the instructions button
 * 
 * @param x The pos x of the top left corner
 * @param y The pos y of the top left corner
 */
void drawInstructionButton(uint16_t x, uint16_t y);

/**
 * @brief Draws the play button animation
 * 
 */
void drawPlayButtonAnimation();

/**
 * @brief Draws the instructions button animation
 * 
 */
void drawInstrButtonAnimation();

/**
 * @brief Displays the menu page
 * 
 */
void displayMenu();

#endif
