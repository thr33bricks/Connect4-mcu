#include "leds.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "logic_game.h"

volatile uint32_t *spiled_base;

/* SPI connected knobs and LEDs registers and keyboard 

#define SPILED_REG_BASE_PHYS  0x43c40000        // Base physical address for SPI-connected peripherals (LEDs, knobs, etc.)
#define SPILED_REG_SIZE       0x00004000        // Total memory size of the SPI LED register block (16 KB)

#define SPILED_REG_LED_LINE_o           0x004   // Offset for the simple red line LED control register (not RGB)
#define SPILED_REG_LED_RGB1_o           0x010   // Offset for RGB LED 1 (24-bit: R[23:16], G[15:8], B[7:0])
#define SPILED_REG_LED_RGB2_o           0x014   // Offset for RGB LED 2 (24-bit: R[23:16], G[15:8], B[7:0])
*/

void initLeds() {
    spiled_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
}

// uint8_t currentPlayer; // 0 for yellow, 1 for red
void setPlayerLed(uint8_t current_player) {
    uint32_t red = 0xFF0000;
    uint32_t yellow = 0xFFFF00;
    uint32_t off = 0x000000;

    if (current_player == 0) {
        setLed1(yellow);
        setLed2(yellow);
    } else {
        setLed1(red);
        setLed2(red);
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

void gameOverLEDS(){
    for (int i=0;i<5;i++){
        setLedsLine(0xFFFF);
        parlcd_delay(500);  // 500 ms
        setLedsLine(0x0000);
        parlcd_delay(500);  // 500 ms
    }
    
}
