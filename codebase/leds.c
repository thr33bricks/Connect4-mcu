#include "leds.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "mzapo_parlcd.h"

volatile uint32_t *spiled_base;
uint32_t red = 0xFF0000;
uint32_t yellow = 0xFFCC00;
uint32_t off = 0x000000;

void initLeds() {
    spiled_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
}

// currentPlayer => 0 for yellow, 1 for red
void setPlayerLed(uint8_t current_player) {
    if (current_player == 0) {
        setLed1(yellow);
        setLed2(yellow);
    } else {
        setLed1(red);
        setLed2(red);
    }
}

void setPlayerLedOff() {
    setLed1(off);
    setLed2(off);
}

void gameOverLEDS(){
    for (int i=0;i<5;i++){
        setLedsLine(0xFFFFFFFF);
        parlcd_delay(500);  // 500 ms
        setLedsLine(0x00000000);
        parlcd_delay(500);  // 500 ms
    }
    
}

void setLed1(uint32_t color) {
    *(spiled_base + SPILED_REG_LED_RGB1_o / 4) = color;
}

void setLed2(uint32_t color) {
    *(spiled_base + SPILED_REG_LED_RGB2_o / 4) = color;
}

void setLedsLine(uint32_t state){
    *(spiled_base + SPILED_REG_LED_LINE_o / 4) = state; 
}
