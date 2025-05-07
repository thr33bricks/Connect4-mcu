#include "rotary_encoder.h"
#include "mzapo_regs.h"
#include <stdint.h>

static uint8_t prev_rot_red = 0;
static uint8_t prev_rot_green = 0;
static uint8_t prev_rot_blue = 0;

int is_red_clicked(void *base) {
    uint32_t val = *(volatile uint32_t *)(base + SPILED_REG_KBDRD_KNOBS_DIRECT_o);
    return (val >> 0) & 0x1;    // Returns 1 if the red button is pressed
}

int is_green_clicked(void *base) {
    uint32_t val = *(volatile uint32_t *)(base + SPILED_REG_KBDRD_KNOBS_DIRECT_o);
    return (val >> 1) & 0x1;    // Returns 1 if the green button is pressed
}

int is_blue_clicked(void *base) {
    uint32_t val = *(volatile uint32_t *)(base + SPILED_REG_KBDRD_KNOBS_DIRECT_o);
    return (val >> 2) & 0x1;    // Returns 1 if the blue button is pressed
}

int get_rotation_red(void *base) {
    uint32_t val = *(volatile uint32_t *)(base + SPILED_REG_KBDRD_KNOBS_DIRECT_o);
    uint8_t new_rot = (val >> 16) & 0xFF;
    int delta = (int8_t)(new_rot - prev_rot_red);
    prev_rot_red = new_rot;
    return delta;
}

int get_rotation_green(void *base) {
    uint32_t val = *(volatile uint32_t *)(base + SPILED_REG_KBDRD_KNOBS_DIRECT_o);
    uint8_t new_rot = (val >> 24) & 0xFF;
    int delta = (int8_t)(new_rot - prev_rot_green);
    prev_rot_green = new_rot;
    return delta;
}

int get_rotation_blue(void *base) {
    uint32_t val = *(volatile uint32_t *)(base + SPILED_REG_KBDRD_KNOBS_DIRECT_o);
    uint8_t new_rot = (val >> 8) & 0xFF;
    int delta = (int8_t)(new_rot - prev_rot_blue);
    prev_rot_blue = new_rot;
    return delta;
}

void init_encoders(void *base) {
    uint32_t val = *(volatile uint32_t *)(base + SPILED_REG_KBDRD_KNOBS_DIRECT_o);
    prev_rot_red = (val >> 16) & 0xFF;
    prev_rot_green = (val >> 24) & 0xFF;
    prev_rot_blue = (val >> 8) & 0xFF;
}
