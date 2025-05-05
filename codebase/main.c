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
      printf("Waitting\n");
      /* Wait till application holding lock releases it or exits */
      serialize_lock(0);
    }
  }

  // Peripherals initialisation
  void *parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  void *spi_leds_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

  if (!parlcd_mem_base || !spi_leds_mem_base) {
    fprintf(stderr, "Error.\n");
    return 1;
  }

  parlcd_hx8357_init(parlcd_mem_base);
  init_lcd(parlcd_mem_base);
  /*
  init_encoders(spi_leds_mem_base);
  init_speaker(spi_leds_mem_base);
  init_leds(spi_leds_mem_base);
  */

  // Game FSM
  GameState state = STATE_MENU;
  while (1) {
    switch (state) {
      case STATE_MENU:
        state = handle_menu(parlcd_mem_base, spi_leds_mem_base);
        break;
      case STATE_INSTRUCTIONS:
        state = handle_instructions(parlcd_mem_base);
        break;
      case STATE_PLAYING:
        state = handle_game(parlcd_mem_base, spi_leds_mem_base);
        break;
      case STATE_GAME_OVER:
        state = handle_game_over(parlcd_mem_base, spi_leds_mem_base);
        break;
    }
  }

  /* Release the lock */
  serialize_unlock();

  return 0;
}
