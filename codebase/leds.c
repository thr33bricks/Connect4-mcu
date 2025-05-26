#include "leds.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "mzapo_parlcd.h"


#define RGB_RED 0xFF0000
#define RGB_YELLOW 0xFFCC00
#define RGB_OFF 0x000000

volatile uint32_t *spiled_base;


void initLeds(){
    spiled_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    setPlayerLedOff();
}

// currentPlayer => 0 for yellow, 1 for red
void setPlayerLed(uint8_t current_player){
    if (current_player == 0) {
        setLed1(RGB_YELLOW);
        setLed2(RGB_YELLOW);
    } else {
        setLed1(RGB_RED);
        setLed2(RGB_RED);
    }
}

void setPlayerLedOff(){
    setLed1(RGB_OFF);
    setLed2(RGB_OFF);
}

void gameOverLEDS(){
    for (int i=0;i<5;i++){
        setLedsLine(0xFFFFFFFF);
        parlcd_delay(500);  // 500 ms
        setLedsLine(0x00000000);
        parlcd_delay(500);  // 500 ms
    }
    
}

void setLed1(uint32_t color){
    *(spiled_base + SPILED_REG_LED_RGB1_o / 4) = color;
}

void setLed2(uint32_t color){
    *(spiled_base + SPILED_REG_LED_RGB2_o / 4) = color;
}

void setLedsLine(uint32_t state){
    *(spiled_base + SPILED_REG_LED_LINE_o / 4) = state; 
}
