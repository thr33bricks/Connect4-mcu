#define _POSIX_C_SOURCE 199309L
#include "rotary_encoder.h"
#include "mzapo_regs.h"
#include "mzapo_phys.h"
#include <time.h>

uint64_t _sampleTime;
uint64_t  _lastSample;
uint64_t  _thisSample;
uint64_t  _reading;
uint8_t _wasPressed;
uint8_t _wasReleased;

void *knobsBase;


void initEncoders() {
    knobsBase = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

    _wasPressed  = 0;
    _wasReleased = 0;
}

uint64_t millis() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)(ts.tv_sec) * 1000 + (ts.tv_nsec / 1000000);
}

 /*
    // Handle interruptions (Red, Blue and Green button + red rotary encoder)
    int was_red_clicked = 0;
    while (1){
        // Scanning red button
        int now = is_red_clicked(spi_leds_base);
        if (now && !was_red_clicked) {
            return STATE_PLAYING;
        }
        was_red_clicked = now;
        usleep(10000); // 10 ms

uint32_t getKnobsMem(){
    return *(volatile uint32_t *)(knobsBase + SPILED_REG_KNOBS_8BIT_o);
}

// pass BTN_RED or BTN_GREEN or BTN_BLUE
uint8_t isDown(uint8_t btn){
    if(btn == BTN_BLUE)
        return ((getKnobsMem() & 0xff000000) >> 24) & 0x1;
    if(btn == BTN_GREEN)
        return ((getKnobsMem() & 0xff000000) >> 25) & 0x1;
    if(btn == BTN_RED)
        return ((getKnobsMem() & 0xff000000) >> 26) & 0x1;
    return 0;
}

void _checkEdge(uint8_t btn) {

	// Take samples only on debounce intervals
	if ((millis()-_sampleTime) > DEBOUNCE_INTERVAL) {
		// Sample button state
		_thisSample = isDown(btn);
		// If it's the same as the last sample then we have a valid reading
		if (_thisSample == _lastSample) {
			// If there's a change, then set pressed/release states (inverse of each other)
			if (_thisSample != _reading) {
				_wasPressed = (_reading == 1) && (_thisSample == 0);
				_wasReleased = !_wasPressed;
			}
			// Save this sample as a reading
			_reading = _thisSample;
		}
		// Use this sample/time as reference for the next detection
		_lastSample = _thisSample;
		_sampleTime = millis();
	}

}

uint8_t wasPressed(uint8_t btn){
	// Update edge detection
	_checkEdge(btn);
	
	// Save and reset edge state  (_wasPressed)
	uint8_t edge = _wasPressed;
	_wasPressed = 0;

	// Return _wasPressed state
	return edge;
}

uint8_t getRotRed() {
    #ifdef REVERSE
    return 63-((getKnobsMem() & 0x00ff0000) >> 18);
    #else
    return (getKnobsMem() & 0x00ff0000) >> 18;
    #endif
}

uint8_t getRotGreen() {
    #ifdef REVERSE
    return 63-((getKnobsMem() & 0x0000ff00) >> 10);
    #else
    return (getKnobsMem() & 0x0000ff00) >> 10;
    #endif
}

uint8_t getRotBlue() {
    #ifdef REVERSE
    return 63-((getKnobsMem() & 0x000000ff) >> 2);
    #else
    return (getKnobsMem() & 0x000000ff) >> 2;
    #endif
}
