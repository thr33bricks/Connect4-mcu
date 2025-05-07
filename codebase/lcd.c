#include "lcd.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

DisBuff disBuff;
void *parlcd_mem_base;

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


void init_lcd(){
    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    parlcd_hx8357_init(parlcd_mem_base);

    disBuff.width = LCD_WIDTH;
    disBuff.height = LCD_HEIGHT;
    for (int i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) {
        disBuff.data[i] = BLUE; 
    }
}

void draw(){
    uint16_t *data = disBuff.data;

    parlcd_write_cmd(parlcd_mem_base, 0x2C);

    for (int i = 0; i < disBuff.height * disBuff.width; i++){
        parlcd_write_data(parlcd_mem_base, data[i]);
    }
}

void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
    // TO DO: Implement Bresenham's line algorithm
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