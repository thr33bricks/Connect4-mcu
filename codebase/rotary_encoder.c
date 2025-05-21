#include "rotary_encoder.h"
#include "mzapo_regs.h"
#include "mzapo_phys.h"
#include <stdint.h>
#include <stdio.h>


    // // Handle interruptions (Red, Blue and Green button + red rotary encoder)
    // int was_red_clicked = 0;
    // while (1){
    //     // Scanning red button
    //     int now = is_red_clicked(spi_leds_base);
    //     if (now && !was_red_clicked) {
    //         return STATE_PLAYING;
    //     }
    //     was_red_clicked = now;
    //     usleep(10000); // 10 ms

uint32_t getKnobsMem(){
    return *(volatile uint32_t *)(knobsBase + SPILED_REG_KNOBS_8BIT_o);
}

void initEncoders() {
    knobsBase = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
}

uint8_t isRedClicked() {
    return ((getKnobsMem() & 0xff000000) >> 26) & 0x1;
}

uint8_t isGreenClicked() {
    return ((getKnobsMem() & 0xff000000) >> 25) & 0x1;
}

uint8_t isBlueClicked() {
    return ((getKnobsMem() & 0xff000000) >> 24) & 0x1;
}

// int clicked(){
//     // 1=blue,2=green,4=red
//     return (getKnobsMem() & 0xff000000) >> 24;
// }

uint8_t getRotRed() {
    #ifdef REVERSE
    return 63-((getKnobsMem() & 0x00ff0000) >> 16)/4;
    #else
    return ((getKnobsMem() & 0x00ff0000) >> 16)/4;
    #endif
}

uint8_t getRotGreen() {
    #ifdef REVERSE
    return 63-((getKnobsMem() & 0x0000ff00) >> 8)/4;
    #else
    return ((getKnobsMem() & 0x0000ff00) >> 8)/4;
    #endif
}

uint8_t getRotBlue() {
    #ifdef REVERSE
    return 63-(getKnobsMem() & 0x000000ff)/4;
    #else
    return (getKnobsMem() & 0x000000ff)/4;
    #endif
}
