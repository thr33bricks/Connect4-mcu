#include <stdint.h>
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "mzapo_parlcd.h"  // pour parlcd_delay()

volatile uint32_t *audiopwm_base;

/*
Simple audio PWM output 

#define AUDIOPWM_REG_BASE_PHYS          0x43c60000  // Base physical address of the AUDIO PWM peripheral
#define AUDIOPWM_REG_SIZE               0x4000  // Size of the memory-mapped region for the AUDIO PWM peripheral (16 KB)

#define AUDIOPWM_REG_CR_o               0x0000  // Offset for the Control Register (may be used for enabling/disabling or resetting the module)
#define AUDIOPWM_REG_PWMPER_o           0x0008  // Period, total duration of one PWM cycle (high + low)
#define AUDIOPWM_REG_PWM_o              0x000C  // This sets how long the signal stays high during one cycle

*/

void initSpeaker() {
    audiopwm_base = map_phys_address(AUDIOPWM_REG_BASE_PHYS, AUDIOPWM_REG_SIZE, 0);
}

void playTone(uint32_t frequency, uint32_t duration_ms) {

    uint32_t pwm_period = 50000000 / frequency;  // 50 MHz horloge par défaut

    *(audiopwm_base + AUDIOPWM_REG_PWMPER_o / 4) = pwm_period;
    *(audiopwm_base + AUDIOPWM_REG_PWM_o / 4) = pwm_period / 2;  // 50% duty cycle (high volume)

    parlcd_delay(duration_ms);

    *(audiopwm_base + AUDIOPWM_REG_PWM_o / 4) = 0;  // Stops the sound
}
