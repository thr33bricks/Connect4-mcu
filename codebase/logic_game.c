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

    return STATE_MENU;
}

GameState handle_instructions(){

}
GameState handle_game(){

}
GameState handle_game_over(){

}