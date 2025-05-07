#include "logic_game.h"
#include "lcd.h"

void init_game() {
    init_lcd();
}
void start_game(){

}

GameState handle_menu(){
    drawBackground(WHITE);
    drawFillRect(50, 70, 430, 270, BLUE);

    drawFillCircle(100, 100, 24, WHITE);
    drawCircle(100, 100, 24, BLACK);

    drawFillCircle(150, 150, 24, YELLOW);

    drawCircle(200, 200, 50, YELLOW);
    drawLine(0, 0, 480, 320, MAGENTA);
    draw();
    // Handle interruptions (Red, Blue and Green button + red rotary encoder)
    /*
        while (1){

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


