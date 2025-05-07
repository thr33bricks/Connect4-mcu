#include "logic_game.h"
#include "lcd.h"

void init_game() {
    init_lcd();
}
void start_game(){

}

GameState handle_menu(){
    draw();

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
    }
    */

    // display_menu();
    return STATE_MENU;
}
GameState handle_instructions(){
    // Handle interruptions (Blue button + green rotary encoder)
    // display_instructions();
}
GameState handle_game(){
    // Handle interruptions (Blue and red button + red rotary encoder)
    // display_game();
}
GameState handle_game_over(){
    // Handle interruptions (Blue and green button)
    // display_game_over();
}


