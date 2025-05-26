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
void displayMenu();
void displayInstructions();
void drawBoard();
void drawScore(uint16_t x, uint16_t y);
void drawHome(uint16_t x, uint16_t y);
void displayGame();
void displayGameOver();

void drawConnect4Title();
void drawPlayButton(uint16_t x, uint16_t y);
void drawInstructionButton(uint16_t x, uint16_t y);

void displayLongText();
void greenTextPosition();

void playScrollSound();
void playClickSound();
void playKorobeiniki();

GameState handleMenu();
GameState handleInstructions();
GameState handleGame();
GameState handleGameOver();

uint8_t checkTie();
uint8_t isGameOver();
uint8_t checkWinner(char color);

#endif