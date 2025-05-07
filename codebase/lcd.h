#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define LCD_WIDTH 480
#define LCD_HEIGHT 320

#define WHITE 0xFFFF
#define BLACK 0x0000
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define YELLOW 0xFFE0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define PINK 0xFC99
#define ORANGE 0xFBE4
#define PURPLE 0x8000
#define GRAY 0x7BEF
#define BROWN 0xA145
#define LIGHT_GRAY 0xD3DF
#define DARK_GRAY 0x7BEF


typedef struct {
    int width;
    int height;
    uint16_t data[LCD_WIDTH * LCD_HEIGHT];
} DisBuff;

void init_lcd();
void draw();
void drawPixel(uint16_t x, uint16_t y, uint16_t color);
void drawBackground(uint16_t color);
void drawRect (uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void drawFillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
void drawFillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
void drawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

#endif