#ifndef PAGE_GAME_H
#define PAGE_GAME_H

#include <stdint.h>

void drawBoard(char board[6][7], uint8_t grad);
void drawHome(uint16_t x, uint16_t y, uint8_t shadow);
void drawHomeButtonAnimation();
void displayGame(char board[6][7], uint8_t scoreYellow, uint8_t scoreRed, uint8_t grad);

uint8_t placeDisc(char board[6][7], uint8_t color);
void searchValidPosX(char board[6][7], uint8_t rot);
void currentSelection(char board[6][7]);
void clearCurrSel(char board[6][7]);

#endif
