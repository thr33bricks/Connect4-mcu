/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  change_me.c      - main file

  include your name there and license for distribution.

  Remove next text: This line should not appear in submitted
  work and project name should be change to match real application.
  If this text is there I want 10 points subtracted from final
  evaluation.

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "serialize_lock.h"

#include "logic_game.h"

#include "lcd.h"
#include "rotary_encoder.h"
#include "speaker.h"
#include "leds.h"


int main(int argc, char *argv[])
{
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

  printf("Game initializing...\n");
  initGame();
  printf("Game initialized\n");

  // Game FSM
  GameState state = STATE_MENU;
  while (1) {
    switch (state) {
      case STATE_MENU:
        state = handleMenu();
        break;
      case STATE_INSTRUCTIONS:
        state = handleInstructions();
        break;
      case STATE_PLAYING:
        state = handleGame();
        break;
      case STATE_GAME_OVER:
        state = handleGameOver();
        break;
    }
  }

  /* Release the lock */
  serialize_unlock();

  return 0;
}
