#ifndef PAGE_INSTR_H
#define PAGE_INSTR_H

#include <stdint.h>

void resetSupLineDisplayed();
void displayLongText();
void greenTextPosition();
void displayScroll();
void drawHomeInstr(uint16_t x, uint16_t y, uint8_t shadow);
void drawHomeInstrBtnAnimation();
void displayInstructions();

#endif
