/**
 * @file page_game_over.h
 * @author Yordan Yordanov and Marie-Ange Rousseau
 * @brief Functions for visualizing the Game over page
 * @version 0.1
 * @date 2025-05-26
 * 
 * @copyright Copyright (c) 2025
 *            license: GNU General Public License v3.0
 * 
 */

#ifndef PAGE_GAME_OVER_H
#define PAGE_GAME_OVER_H

#include <stdint.h>

/**
 * @brief Draws the title, who wins or tie
 * 
 * @param winner 'y', 'r' or 't'
 */
void drawGameOverTitle(uint8_t winner);

/**
 * @brief Draws a blue menu button
 * 
 * @param x Pos x of top left corner
 * @param y Pos y of top left corner
 */
void drawMenuButton(uint16_t x, uint16_t y);

/**
 * @brief Draws the play again button
 * 
 * @param x Pos x of top left corner
 * @param y Pos y of top left corner
 */
void drawPlAgainButton(uint16_t x, uint16_t y);

/**
 * @brief Draws the play again button animation 
 * 
 * Makes the outline gradually wider
 * 
 */
void drawPlAgainButtonAnimation();

/**
 * @brief Draws the menu button animation
 * 
 * Makes the outline gradually wider
 */
void drawMenuButtonAnimation();

/**
 * @brief Displays the game over page
 * 
 * @param winner 'y', 'r' or 't'
 * @param scoreYellow The score of yellow player
 * @param scoreRed The score of red player
 */
void displayGameOver(uint8_t winner, uint8_t scoreYellow, uint8_t scoreRed);

/**
 * @brief Draws the game score at a specified location
 * 
 * @param x Pos x of top left corner
 * @param y Pos y of top left corner
 * @param scoreYellow The score of yellow player
 * @param scoreRed The score of red player
 */
void drawScore(uint16_t x, uint16_t y, uint8_t scoreYellow, uint8_t scoreRed);

#endif
