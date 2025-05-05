#include "logic_game.h"
#include "lcd.h"

void init_game() {
    init_lcd();
}
void start_game(){

}

GameState handle_menu(){
    draw();

    return STATE_MENU;
}

GameState handle_instructions(){

}
GameState handle_game(){

}
GameState handle_game_over(){

}