/**
 * @file logic_misc.h
 * @author Yordan Yordanov and Marie-Ange Rousseau
 * @brief Misc functions complementing the game logic
 * @version 0.1
 * @date 2025-05-26
 * 
 * @copyright Copyright (c) 2025
 *            license: GNU General Public License v3.0
 * 
 */

#ifndef LOGIC_MISC_H
#define LOGIC_MISC_H

#include <stdint.h>

/**
 * @brief Checks if there is a winner
 * and who or whether the game is tie
 * 
 * @param board The board matrix
 * @return uint8_t
 * 
 * 'y' => yellow, 'r' => red, 't' => tie
 * 0 => no winner yet
 */
uint8_t isGameOver(char board[6][7]);

/**
 * @brief Checks if the game is tie
 * 
 * @param board The board matrix
 * @return uint8_t
 * 
 * 1 => tie, 0 => no tie
 */
uint8_t checkTie(char board[6][7]);

/**
 * @brief Checks if the passed colour wins
 * 
 * @param board The board matrix
 * @param color 'y' or 'r'
 * @return uint8_t 
 * 
 * 1 => winner, 0 => not a winner
 */
uint8_t checkWinner(char board[6][7], char color);

/**
 * @brief Plays a scroll sound with the
 * piezo buzzer
 * 
 */
void playScrollSound();

/**
 * @brief Plays a click sound with the
 * piezo buzzer
 * 
 */
void playClickSound();

#endif
