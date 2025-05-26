#ifndef LOGIC_MISC_H
#define LOGIC_MISC_H

#include <stdint.h>

uint8_t isGameOver(char board[6][7]);
uint8_t checkTie(char board[6][7]);
uint8_t checkWinner(char board[6][7], char color);

void playScrollSound();
void playClickSound();

#endif
