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

int isGameOver(char color);

#endif