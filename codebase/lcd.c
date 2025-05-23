#include "lcd.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"
#include <stdio.h>


DisBuff disBuff;
void *parlcd_mem_base;


void initLcd(){
    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    parlcd_hx8357_init(parlcd_mem_base);

    disBuff.width = LCD_WIDTH;
    disBuff.height = LCD_HEIGHT;
}

void draw(){
    uint16_t *data = disBuff.data;

    parlcd_write_cmd(parlcd_mem_base, 0x2C);

    for (int i = 0; i < disBuff.height * disBuff.width; i++){
        parlcd_write_data(parlcd_mem_base, data[i]);
    }

    // Messy image for some reason :X
    // for (int i = 0; i < disBuff.height * disBuff.width; i+=2){
    //     parlcd_write_data2x(parlcd_mem_base, (((uint32_t)data[i])<<16) | (uint32_t)data[i+1]);
    // }
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

void drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
    drawLine(x, y, x + width - 1, y, color);
    drawLine(x, y, x, y + height - 1, color);
    drawLine(x, y + height - 1, x + width - 1, y + height - 1, color);
    drawLine(x + width - 1, y, x + width - 1, y + height - 1, color);
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
    int32_t dx = abs(x2 - x1);
    int32_t dy = abs(y2 - y1);
    int32_t sx = (x1 < x2) ? 1 : -1;
    int32_t sy = (y1 < y2) ? 1 : -1;
    int32_t err = dx - dy;

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

void drawPixelBig(int x, int y, int scale, uint16_t color) {
    for (int dx = 0; dx < scale; dx++) {
        for (int dy = 0; dy < scale; dy++) {
            drawPixel(x + dx, y + dy, color);
        }
    }
}

// Size 1 and 2 are supported
// Font 1: 8x16
// Font 2: 14x16
void drawText(uint8_t size, int x, int y, char *text, uint16_t color, uint8_t font) {
    int cursorX = x;

    // Select font by size (expandable)
    font_descriptor_t *fontPtr = (font == 1) ? &font_rom8x16 : &font_winFreeSystem14x16;

    // Sanity check
    if (!fontPtr || !fontPtr->bits) return;

    while (*text || text == 0) {
        unsigned char c = *text++;
        int charIndex = c - fontPtr->firstchar;

        // Bounds check
        if (charIndex < 0 || charIndex >= fontPtr->size) {
            charIndex = fontPtr->defaultchar - fontPtr->firstchar;
            if (charIndex < 0 || charIndex >= fontPtr->size) continue;
        }

        // Determine character width
        int charWidth = (fontPtr->width) ? fontPtr->width[charIndex] : fontPtr->maxwidth;

        // Determine bits per row (in 16-bit words)
        int bw = (fontPtr->maxwidth + 15) / 16;

        // Get pointer to character bitmap
        const font_bits_t *charBitmap;
        if (fontPtr->offset) {
            // Use offset table
            uint32_t offset = fontPtr->offset[charIndex];

            // Optional: bounds check to be safe
            if (offset >= fontPtr->bits_size) continue;

            charBitmap = &fontPtr->bits[offset];
        } else {
            // Calculate offset manually if no offset table
            charBitmap = &fontPtr->bits[charIndex * bw * fontPtr->height];
        }

        // Draw character bitmap
        for (int row = 0; row < fontPtr->height; ++row) {
            font_bits_t rowBits = *charBitmap++;

            for (int col = 0; col < charWidth; ++col) {
                if (rowBits & (1 << (15 - col))) {
                    (size == 1) ? drawPixel(cursorX + col, y + row, color) :
                        drawPixelBig(cursorX + col * size, y + row * size, size, color);
                }
            }
        }

        // Move cursor forward
        cursorX += charWidth + size*((size == 1) ? 2 : 6); // Add pixel spacing
    }
}
