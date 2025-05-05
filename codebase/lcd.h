#ifndef LCD_H
#define LCD_H

#include "mzapo_parlcd.h"
#include "mzapo_regs.h"

#define LCD_WIDTH 480
#define LCD_HEIGHT 320
#define LCD_BASE_ADDR PARLCD_REG_BASE_PHYS

typedef struct {
    int width;
    int height;
    uint16_t data[LCD_WIDTH * LCD_HEIGHT];
} DisBuff;

void init_lcd();
void draw();

#endif