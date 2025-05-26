/**
 * @file logic_game.h
 * @author Yordan Yordanov and Marie-Ange Rousseau
 * @brief The main logic of the game, FSM representing
 * all the pages and transitions between them
 * @version 0.1
 * @date 2025-05-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef LOGIC_GAME_H
#define LOGIC_GAME_H

#include <stdint.h>

/**
 * @brief All states for the pages FSM
 * 
 */
typedef enum {
    STATE_MENU,
    STATE_INSTRUCTIONS,
    STATE_PLAYING,
    STATE_GAME_OVER
} GameState;


/**
 * @brief Fills the board with 'o' chars
 * which represent empty cells
 * 
 */
void initBoard();

/**
 * @brief Inits a new game. Resets the 
 * selected x pos on the board, resets 
 * the rotary encoder state, inits the 
 * board and more
 * 
 */
void initGame();

// FSM part

/**
 * @brief Handles the menu page
 * 
 * @return GameState
 * 
 * That's how a page changes or 
 * stays the same if the same
 * state is returned
 */
GameState handleMenu();

/**
 * @brief Handles the instructions page
 * 
 * @return GameState 
 */
GameState handleInstructions();

/**
 * @brief Handles the game page
 * 
 * @param grad A value that gradually oscillates
 * between 2 thresholds, currently used as 
 * the cell selection gradient
 * 
 * @return GameState 
 */
GameState handleGame(uint8_t grad);

/**
 * @brief Handles the game over page
 * 
 * @return GameState 
 */
GameState handleGameOver();

#endif
