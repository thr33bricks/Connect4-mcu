#include "lcd.h"
#include "mzapo_parlcd.h"

DisBuff disBuff;

void init_lcd(){
    disBuff.width = LCD_WIDTH;
    disBuff.height = LCD_HEIGHT;
    for (int i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) {
        disBuff.data[i] = 0xFFFF; // White color
    }
}
void draw(){
    uint16_t *data = disBuff.data;

    parlcd_write_cmd(LCD_BASE_ADDR, 0x2C);

    for (int i = 0; i < disBuff.height * disBuff.width; i++){
        parlcd_write_data(LCD_BASE_ADDR, data[i]);
    }
}