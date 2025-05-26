#ifndef LOGIC_GAME_H
#define LOGIC_GAME_H

#include <stdint.h>

typedef enum {
    STATE_MENU,
    STATE_INSTRUCTIONS,
    STATE_PLAYING,
    STATE_GAME_OVER
} GameState;


// Init functions
void initBoard();
void initGame();

// FSM
GameState handleMenu();
GameState handleInstructions();
GameState handleGame(uint8_t grad);
GameState handleGameOver();

#endif
