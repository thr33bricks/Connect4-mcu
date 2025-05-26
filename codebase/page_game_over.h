#ifndef PAGE_GAME_OVER_H
#define PAGE_GAME_OVER_H

#include <stdint.h>

void drawGameOverTitle(uint8_t winner);
void drawMenuButton(uint16_t x, uint16_t y);
void drawPlAgainButton(uint16_t x, uint16_t y);
void drawPlAgainButtonAnimation();
void drawMenuButtonAnimation();
void displayGameOver(uint8_t winner, uint8_t scoreYellow, uint8_t scoreRed);
void drawScore(uint16_t x, uint16_t y, uint8_t scoreYellow, uint8_t scoreRed);

#endif
