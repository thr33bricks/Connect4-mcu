#define _POSIX_C_SOURCE 199309L
#include "rotary_encoder.h"

#include <time.h>
#include <stdlib.h>

#include "mzapo_regs.h"
#include "mzapo_phys.h"
#include "settings.h"

// BTN RED
uint64_t _sampleTimeRed;
uint64_t  _lastSampleRed;
uint64_t  _thisSampleRed;
uint64_t  _readingRed;
uint8_t _wasPressedRed;
uint8_t _wasReleasedRed;

// BTN GREEN
uint64_t _sampleTimeGreen;
uint64_t  _lastSampleGreen;
uint64_t  _thisSampleGreen;
uint64_t  _readingGreen;
uint8_t _wasPressedGreen;
uint8_t _wasReleasedGreen;

// BTN BLUE
uint64_t _sampleTimeBlue;
uint64_t  _lastSampleBlue;
uint64_t  _thisSampleBlue;
uint64_t  _readingBlue;
uint8_t _wasPressedBlue;
uint8_t _wasReleasedBlue;

// Rotary encoders
uint8_t prevRotRed = 0;
uint8_t prevRotGreen = 0;
uint8_t prevRotBlue = 0;

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
    if(btn == ROT_BLUE)
        return (getKnobsMem() >> 24) & 0x1;
    if(btn == ROT_GREEN)
        return (getKnobsMem() >> 25) & 0x1;
    if(btn == ROT_RED)
        return (getKnobsMem() >> 26) & 0x1;
    return 0;
}

void setSampleTime(uint8_t btn) {
    if(btn == ROT_BLUE)
        _sampleTimeBlue = millis();
    if(btn == ROT_GREEN)
        _sampleTimeGreen = millis();
    if(btn == ROT_RED)
        _sampleTimeRed = millis();
}
uint64_t getSampleTime(uint8_t btn) {
    if(btn == ROT_BLUE)
        return _sampleTimeBlue;
    if(btn == ROT_GREEN)
        return _sampleTimeGreen;
    if(btn == ROT_RED)
        return _sampleTimeRed;
    return 0;
}

void setLastSample(uint8_t btn) {
    if(btn == ROT_BLUE)
        _lastSampleBlue = _thisSampleBlue;
    if(btn == ROT_GREEN)
        _lastSampleGreen = _thisSampleGreen;
    if(btn == ROT_RED)
        _lastSampleRed = _thisSampleRed;
}
uint64_t getLastSample(uint8_t btn) {
    if(btn == ROT_BLUE)
        return _lastSampleBlue;
    if(btn == ROT_GREEN)
        return _lastSampleGreen;
    if(btn == ROT_RED)
        return _lastSampleRed;
    return 0;
}
void setThisSample(uint8_t btn) {
    if(btn == ROT_BLUE)
        _thisSampleBlue = isDown(btn);
    if(btn == ROT_GREEN)
        _thisSampleGreen = isDown(btn);
    if(btn == ROT_RED)
        _thisSampleRed = isDown(btn);
}
uint64_t getThisSample(uint8_t btn) {
    if(btn == ROT_BLUE)
        return _thisSampleBlue;
    if(btn == ROT_GREEN)
        return _thisSampleGreen;
    if(btn == ROT_RED)
        return _thisSampleRed;
    return 0;
}
void setReading(uint8_t btn) {
    if(btn == ROT_BLUE)
        _readingBlue = _thisSampleBlue;
    if(btn == ROT_GREEN)
        _readingGreen = _thisSampleGreen;
    if(btn == ROT_RED)
        _readingRed = _thisSampleRed;
}
uint64_t getReading(uint8_t btn) {
    if(btn == ROT_BLUE)
        return _readingBlue;
    if(btn == ROT_GREEN)
        return _readingGreen;
    if(btn == ROT_RED)
        return _readingRed;
    return 0;
}
void setWasPressed(uint8_t btn, uint8_t val) {
    if(btn == ROT_BLUE)
        _wasPressedBlue = val;
    if(btn == ROT_GREEN)
        _wasPressedGreen = val;
    if(btn == ROT_RED)
        _wasPressedRed = val;
}
uint8_t getWasPressed(uint8_t btn) {
    if(btn == ROT_BLUE)
        return _wasPressedBlue;
    if(btn == ROT_GREEN)
        return _wasPressedGreen;
    if(btn == ROT_RED)
        return _wasPressedRed;
    return 0;
}
void invertWasReleased(uint8_t btn) {
    if(btn == ROT_BLUE)
        _wasReleasedBlue = !_wasReleasedBlue;
    if(btn == ROT_GREEN)
        _wasReleasedGreen = !_wasReleasedGreen;
    if(btn == ROT_RED)
        _wasReleasedRed = !_wasReleasedRed;
}
uint8_t getWasReleased(uint8_t btn) {
    if(btn == ROT_BLUE)
        return _wasReleasedBlue;
    if(btn == ROT_GREEN)
        return _wasReleasedGreen;
    if(btn == ROT_RED)
        return _wasReleasedRed;
    return 0;
}

void _checkEdge(uint8_t btn) {
	// Take samples only on debounce intervals
	if ((millis()-getSampleTime(btn)) > DEBOUNCE_INTERVAL) {
		// Sample button state
		setThisSample(btn);
		// If it's the same as the last sample then we have a valid reading
		if (getThisSample(btn) == getLastSample(btn)) {
			// If there's a change, then set pressed/release states (inverse of each other)
			if (getThisSample(btn) != getReading(btn)) {
				setWasPressed(btn, (getReading(btn) == 1) && (getThisSample(btn) == 0));
				invertWasReleased(btn);
			}
			// Save this sample as a reading
			setReading(btn);
		}
		// Use this sample/time as reference for the next detection
		setLastSample(btn);
		setSampleTime(btn);
	}

}

uint8_t wasPressed(uint8_t btn){
	// Update edge detection
	_checkEdge(btn);
	
	// Save and reset edge state  (_wasPressed)
	uint8_t edge = getWasPressed(btn);
	setWasPressed(btn, 0);

	// Return _wasPressed state
	return edge;
}

uint8_t getRotRed() {
    #ifdef REVERSE_ROT
    return 63-((getKnobsMem() & 0x00ff0000) >> 18);
    #else
    return (getKnobsMem() & 0x00ff0000) >> 18;
    #endif
}

uint8_t getRotGreen() {
    #ifdef REVERSE_ROT
    return 63-((getKnobsMem() & 0x0000ff00) >> 10);
    #else
    return (getKnobsMem() & 0x0000ff00) >> 10;
    #endif
}

uint8_t getRotBlue() {
    #ifdef REVERSE_ROT
    return 63-((getKnobsMem() & 0x000000ff) >> 2);
    #else
    return (getKnobsMem() & 0x000000ff) >> 2;
    #endif
}

void resetRot(uint8_t enc) {
    if(enc == ROT_RED)
        prevRotRed = getRotRed();
    else if(enc == ROT_GREEN)
        prevRotGreen = getRotGreen();
    else if(enc == ROT_BLUE)
        prevRotBlue = getRotBlue();
}

uint8_t getRotDir(uint8_t enc) {
    uint8_t rot = 0;
    int8_t delta = 0;

    if(enc == ROT_RED){
        rot = getRotRed();
        delta = rot - prevRotRed;
        prevRotRed = rot;
    }
    else if(enc == ROT_GREEN){
        rot =  getRotGreen();
        delta = rot - prevRotGreen;
        prevRotGreen = rot;
    }
    else if(enc == ROT_BLUE){
        rot = getRotBlue();
        delta = rot - prevRotBlue;
        prevRotBlue = rot;
    }

    // No rotation
    if(delta == 0)
        return 0;

    // Value overflows
    if(abs(delta) > 32) {
        return (delta > 0) ? 'l' : 'r';
    }
    return (delta > 0) ? 'r' : 'l';
}
