#include <stdint.h>
#include <stdio.h>
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "mzapo_parlcd.h"  // pour parlcd_delay()

#define VOL 2 // Volume level (0-100)

volatile uint32_t *audiopwm_base;

void initSpeaker() {
    audiopwm_base = map_phys_address(AUDIOPWM_REG_BASE_PHYS, AUDIOPWM_REG_SIZE, 0);
    //*(audiopwm_base + AUDIOPWM_REG_CR_o) = 0xFF;
}

void playTone(uint32_t frequency, uint32_t duration_ms) {
    uint32_t pwm_period = (100000000 / frequency);  // 100 MHz clock frequency

    *(audiopwm_base + AUDIOPWM_REG_PWM_o/4) = VOL * 1000;  // Set volume
    *(audiopwm_base + AUDIOPWM_REG_PWMPER_o/4) = pwm_period;
    parlcd_delay(duration_ms);
    *(audiopwm_base + AUDIOPWM_REG_PWM_o/4) = 0;  // End tone
}
