#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define LCD_WIDTH 480
#define LCD_HEIGHT 320

typedef struct {
    int width;
    int height;
    uint16_t data[LCD_WIDTH * LCD_HEIGHT];
} DisBuff;

void init_lcd();
void draw();

/*
void display_menu();
void display_instructions();
void display_game();
void display_game_over();
*/

#endif