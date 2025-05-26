/*******************************************************************
  Connect 4 game 
  designed by Yordan YORDANOV & Marie-Ange ROUSSEAU
  Spring semester 2025 - CVUT - Computer architecture

  Source :
  - Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>

#include "serialize_lock.h"
#include "logic_game.h"
#include "settings.h"
#include "lcd.h"
#include "rotary_encoder.h"
#include "speaker.h"
#include "leds.h"

int8_t step = -1;
uint8_t currGrad = END_GRAD-1;
uint64_t lastUpdate = 0;

void updateGrad(){
  uint64_t now = millis();
  if (now - lastUpdate >= INTERVAL_GRAD) {
    lastUpdate = now;

    if (currGrad < END_GRAD && currGrad > START_GRAD)
      currGrad += step;
    else{
      step *= -1;
      currGrad += step;
    }
  }
}

int main(int argc, char *argv[]){
  /* Serialize execution of applications */

  /* Try to acquire lock the first */
  if (serialize_lock(1) <= 0) {
    printf("System is occupied\n");

    if (1) {
      printf("Waiting\n");
      /* Wait till application holding lock releases it or exits */
      serialize_lock(0);
    }
  }

  initEncoders();
  initLcd();
  initSpeaker();
  initLeds();
  printf("Peripherals initialized\n");

  lastUpdate = millis();

  // Game FSM
  GameState state = STATE_MENU;
  while (1) {
    updateGrad();

    switch (state) {
      case STATE_MENU:
        state = handleMenu();
        break;
      case STATE_INSTRUCTIONS:
        state = handleInstructions();
        break;
      case STATE_PLAYING:
        state = handleGame(currGrad);
        break;
      case STATE_GAME_OVER:
        state = handleGameOver();
        break;
    }
  }

  printf("Goodbye!\n");

  /* Release the lock */
  serialize_unlock();

  return 0;
}
