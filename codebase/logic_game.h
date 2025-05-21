#ifndef LOGIC_GAME_H
#define LOGIC_GAME_H

#include <stdint.h>
#include <stdlib.h>

typedef enum {
    STATE_MENU,
    STATE_INSTRUCTIONS,
    STATE_PLAYING,
    STATE_GAME_OVER
} GameState;

// 'o' => empty
// 'y' => yellow
// 'r' => red
// 'g' => selection
char board[6][7];

// Game variables
uint8_t lastPosX;
uint8_t currPosX;
uint8_t currPosY;
uint8_t currentPlayer; // 0 for yellow, 1 for red
uint8_t scoreYellow;
uint8_t scoreRed;


void initBoard();
void initGame();
void startGame();
void displayMenu();
void displayInstructions();
void drawBoard();
void drawScore();
void displayGame();
void displayGameOver();

GameState handleMenu();
GameState handleInstructions();
GameState handleGame();
GameState handleGameOver();

#endif