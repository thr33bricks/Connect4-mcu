/**
 * @file lcd.h
 * @author Yordan Yordanov and Marie-Ange Rousseau
 * @brief LCD display library
 * @version 0.1
 * @date 2025-05-26
 * 
 * @copyright Copyright (c) 2025
 *            license: GNU General Public License v3.0
 * 
 */

#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define LCD_WIDTH 480
#define LCD_HEIGHT 320

#define WHITE 0xFFFF
#define BLACK 0x0000
#define RED 0xF800
#define GREEN 0x07E0
#define LIGHT_GREEN 0xd7fb
#define DARK_GREEN 0x14a5
#define MID_GREEN 0x6e8f
#define BLUE 0x001F
#define YELLOW 0xFFE0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define PINK 0xFC99
#define ORANGE 0xFBE4
#define PURPLE 0x8000
#define GRAY 0x7BCF
#define BROWN 0xA145
#define LIGHT_GRAY 0xd6da
#define DARK_GRAY 0x7BEF


typedef struct {
    int width;
    int height;
    uint16_t data[LCD_WIDTH * LCD_HEIGHT];
} DisBuff;

/**
 * @brief Maps memory and inits the display
 * 
 */
void initLcd();

/**
 * @brief Updates the display
 * 
 */
void draw();

/**
 * @brief Draws a single pixel
 * 
 * @param x Pos x
 * @param y Pos y
 * @param color RGB565-coded colour
 */
void drawPixel(uint16_t x, uint16_t y, uint16_t color);

/**
 * @brief Draws with a single color over every pixel on the screen
 * 
 * @param color RGB565-coded colour
 */
void drawBackground(uint16_t color);

/**
 * @brief Draws a rectangle
 * 
 * @param x Pos x of left corner
 * @param y Pos y of left corner
 * @param width Width in pixels
 * @param height Height in pixels
 * @param color RGB565-coded colour
 */
void drawRect (uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);

/**
 * @brief Draws a filled rectangle
 * 
 * @param x Pos x of left corner
 * @param y Pos y of left corner
 * @param width Width in pixels
 * @param height Height in pixels
 * @param color RGB565-coded colour
 */
void drawFillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);

/**
 * @brief Draws a circle
 * 
 * @param x0 Pos x of the center
 * @param y0 Pos y of the center
 * @param r Radius in pixels
 * @param color RGB565-coded colour
 */
void drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);

/**
 * @brief Draws a filled circle
 * 
 * @param x0 Pos x of the center
 * @param y0 Pos y of the center
 * @param r Radius in pixels
 * @param color RGB565-coded colour
 */
void drawFillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);

/**
 * @brief Draws a triangle
 * 
 * @param x1 Pos x of 1 point
 * @param y1 Pos y of 1 point
 * @param x2 Pos x of 2 point
 * @param y2 Pos y of 2 point
 * @param x3 Pos x of 3 point
 * @param y3 Pos y of 3 point
 * @param color RGB565-coded colour
 */
void drawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);

/**
 * @brief Draws a line
 * 
 * @param x1 Pos x of 1 point
 * @param y1 Pos y of 1 point
 * @param x2 Pos x of 2 point
 * @param y2 Pos y of 2 point
 * @param color RGB565-coded colour
 */
void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

/**
 * @brief Draws text
 * 
 * @param size Size of text
 * @param x Pos x of bottom left corner of 1 char
 * @param y Pos y of bottom left corner of 1 char
 * @param text Pointer to the text string
 * @param color RGB565-coded colour
 * @param font 1 - font_rom8x16, 2 - font_winFreeSystem14x16
 */
void drawText(uint8_t size, int x, int y, char *text, uint16_t color, uint8_t font);

/**
 * @brief Sets shadow behind text
 * 
 * @param shadow How wide is the shadow in pixels
 * @param color RGB565-coded colour
 */
void setShadow(uint8_t shadow, uint16_t color);

#endif
