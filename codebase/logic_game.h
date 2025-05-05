#ifndef LOGIC_GAME_H
#define LOGIC_GAME_H

typedef enum {
    STATE_MENU,
    STATE_INSTRUCTIONS,
    STATE_PLAYING,
    STATE_GAME_OVER
} GameState;


void init_game();
void start_game();
GameState handle_menu();
GameState handle_instructions();
GameState handle_game();
GameState handle_game_over();

#endif