/**
 * @file speaker.h
 * @author Yordan Yordanov and Marie-Ange Rousseau
 * @brief A simple piezo buzzer library
 * @version 0.1
 * @date 2025-05-27
 * 
 * @copyright Copyright (c) 2025
 *            license: GNU General Public License v3.0
 * 
 */

#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>

/**
 * @brief Memory map
 * 
 */
void initSpeaker();

/**
 * @brief Plays a frequency for a duration
 * 
 * @param frequency Hz
 * @param duration_ms duration in ms
 */
void playTone(uint32_t frequency, uint32_t duration_ms);

#endif
