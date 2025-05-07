#include "lcd.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

DisBuff disBuff;
void *parlcd_mem_base;


void init_lcd(){
    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    parlcd_hx8357_init(parlcd_mem_base);

    disBuff.width = LCD_WIDTH;
    disBuff.height = LCD_HEIGHT;
<<<<<<< HEAD
=======
    for (int i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) {
        disBuff.data[i] = BLUE; 
    }
>>>>>>> 4f742dfe08f020bc4918d57e11b286b21c4ee98b
}

void draw(){
    uint16_t *data = disBuff.data;

    parlcd_write_cmd(parlcd_mem_base, 0x2C);

    for (int i = 0; i < disBuff.height * disBuff.width; i++){
        parlcd_write_data(parlcd_mem_base, data[i]);
    }
}

void drawPixel(uint16_t x, uint16_t y, uint16_t color){
    if (x < LCD_WIDTH && y < LCD_HEIGHT) {
        disBuff.data[y * LCD_WIDTH + x] = color;
    }
}

void drawBackground(uint16_t color){
    for (int i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) {
        disBuff.data[i] = color;
    }
}

void drawRect (uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color){
    drawLine(x, y, x+width, y, color);
    drawLine(x, y, x, y+height, color);
    drawLine(x, y+height, x+width, y+height, color);
    drawLine(x+width, y, x+width, y+height, color);
}

void drawFillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color){
    for (uint16_t i = 0; i < width; i++) {
        for (uint16_t j = 0; j < height; j++) {
            drawPixel(x + i, y + j, color);
        }
    }
}

void drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color){
    int16_t x = r;
    int16_t y = 0;
    int16_t err = 0;

    while (x >= y) {
        drawPixel(x0 + x, y0 + y, color);
        drawPixel(x0 + y, y0 + x, color);
        drawPixel(x0 - y, y0 + x, color);
        drawPixel(x0 - x, y0 + y, color);
        drawPixel(x0 - x, y0 - y, color);
        drawPixel(x0 - y, y0 - x, color);
        drawPixel(x0 + y, y0 - x, color);
        drawPixel(x0 + x, y0 - y, color);

        if (err <= 0) {
            err += 2 * ++y + 1;
        }
        if (err > 0) {
            err -= 2 * --x;
        }
    }
}

void drawFillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color){
    for (int16_t y = -r; y <= r; y++) {
        for (int16_t x = -r; x <= r; x++) {
            if (x * x + y * y <= r * r) {
                drawPixel(x0 + x, y0 + y, color);
            }
        }
    }
}

void drawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color){
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x3, y3, color);
    drawLine(x3, y3, x1, y1, color);
}

void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
    uint16_t dx = abs(x2 - x1);
    uint16_t dy = abs(y2 - y1);
    uint16_t sx = (x1 < x2) ? 1 : -1;
    uint16_t sy = (y1 < y2) ? 1 : -1;
    uint16_t err = dx - dy;

    while (1) {
        drawPixel(x1, y1, color);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

/*
void display_menu(){
    // Title : "Connect 4"
    // Red Play button + number of games selection
    // Green Instructions button
    // Blue Close button 
}
void display_instructions(){
    // Title : "Instructions"
    // Instructions text
    // Blue back button
    // Green cursor
}
void display_game(){
    // Scores
    // Grid
    // Column selection with de red button & rotary encoder
    // Blue menu button
}
void display_game_over(){
    // Title : "Game over"
    // Scores
    // Blue "Menu" button
    // Green "Play again" button
}
*/