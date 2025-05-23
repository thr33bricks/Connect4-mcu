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

// RED
uint64_t _sampleTimeRed;
uint64_t  _lastSampleRed;
uint64_t  _thisSampleRed;
uint64_t  _readingRed;
uint8_t _wasPressedRed;
uint8_t _wasReleasedRed;

// GREEN
uint64_t _sampleTimeGreen;
uint64_t  _lastSampleGreen;
uint64_t  _thisSampleGreen;
uint64_t  _readingGreen;
uint8_t _wasPressedGreen;
uint8_t _wasReleasedGreen;

// BLUE
uint64_t _sampleTimeBlue;
uint64_t  _lastSampleBlue;
uint64_t  _thisSampleBlue;
uint64_t  _readingBlue;
uint8_t _wasPressedBlue;
uint8_t _wasReleasedBlue;

void *knobsBase;


void initEncoders() {
    knobsBase = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

    _wasPressedRed  = 0;
    _wasReleasedRed = 0;
    _wasPressedGreen  = 0;
    _wasReleasedGreen = 0;
    _wasPressedBlue  = 0;
    _wasReleasedBlue = 0;
}

uint64_t millis() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)(ts.tv_sec) * 1000 + (ts.tv_nsec / 1000000);
}

uint32_t getKnobsMem(){
    return *(volatile uint32_t *)(knobsBase + SPILED_REG_KNOBS_8BIT_o);
}

// pass BTN_RED or BTN_GREEN or BTN_BLUE
uint8_t isDown(uint8_t btn){
    if(btn == BTN_BLUE)
        return (getKnobsMem() >> 24) & 0x1;
    if(btn == BTN_GREEN)
        return (getKnobsMem() >> 25) & 0x1;
    if(btn == BTN_RED)
        return (getKnobsMem() >> 26) & 0x1;
    return 0;
}

// void setSampleTime(uint8_t btn) {
//     if(btn == BTN_BLUE)
//         _sampleTimeBlue = millis();
//     if(btn == BTN_GREEN)
//         _sampleTimeGreen = millis();
//     if(btn == BTN_RED)
//         _sampleTimeRed = millis();
// }
// void getSampleTime(uint8_t btn) {
//     if(btn == BTN_BLUE)
//         return _sampleTimeBlue;
//     if(btn == BTN_GREEN)
//         return _sampleTimeGreen;
//     if(btn == BTN_RED)
//         return _sampleTimeRed;
//     return 0;
// }

    

void _checkEdge(uint8_t btn) {
    // uint64_t _sampleTime = get
    // uint64_t _lastSample;
    // uint64_t _thisSample;
    // uint64_t _readingRed;
    // uint8_t _wasPressedRed;
    // uint8_t _wasReleasedRed;

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
    return 0;
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
