/**
 * @file page_game.h
 * @author Yordan Yordanov and Marie-Ange Rousseau
 * @brief Functions for visualizing the Game page
 * @version 0.1
 * @date 2025-05-26
 * 
 * @copyright Copyright (c) 2025
 *            license: GNU General Public License v3.0
 * 
 */

#ifndef PAGE_GAME_H
#define PAGE_GAME_H

#include <stdint.h>

/**
 * @brief Resets the current x pos selector
 * 
 */
void resetcurrPosX();

/**
 * @brief Draws the game board
 * 
 * @param board The board matrix
 * @param grad A value oscillating between
 * two thresholds
 */
void drawBoard(char board[6][7], uint8_t grad);

/**
 * @brief Draws a circle home button
 * 
 * @param x Pos x
 * @param y Pos y
 * @param shadow 
 * 1 => has shadow, 0 => no shadow
 */
void drawHome(uint16_t x, uint16_t y, uint8_t shadow);

/**
 * @brief Draws the animation for the home button 
 * 
 * Makes the outline gradually wider
 * 
 */
void drawHomeButtonAnimation();

/**
 * @brief Displays the game page
 * 
 * @param board The board matrix
 * @param scoreYellow The score of the yellow player
 * @param scoreRed The score of the red player
 * @param grad A value oscillating between 
 * two thresholds
 */
void displayGame(char board[6][7], uint8_t scoreYellow, uint8_t scoreRed, uint8_t grad);

/**
 * @brief Places a disc in a non-empty cell
 * 
 * @param board The board matrix
 * @param color 'y' or 'r'
 * @return uint8_t 1 => success, 0 => failure
 */
uint8_t placeDisc(char board[6][7], uint8_t color);

/**
 * @brief Searches for a non-empty column based on 
 * the direction of the knob ('r' or 'l')
 * 
 * @param board The board matrix
 * @param rot The rotation direction ('r' or 'l')
 */
void searchValidPosX(char board[6][7], uint8_t rot);

/**
 * @brief Updates the current column selection
 * based on the knob position
 * 
 * @param board The board matrix
 */
void currentSelection(char board[6][7]);

/**
 * @brief Removes the green selector for the board
 * 
 * @param board The board matrix
 */
void clearCurrSel(char board[6][7]);

#endif
