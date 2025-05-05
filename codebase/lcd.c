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
    for (int i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) {
        disBuff.data[i] = 0xFFFF; // White color
    }
}
void draw(){
    uint16_t *data = disBuff.data;

    parlcd_write_cmd(parlcd_mem_base, 0x2C);

    for (int i = 0; i < disBuff.height * disBuff.width; i++){
        parlcd_write_data(parlcd_mem_base, data[i]);
    }
}