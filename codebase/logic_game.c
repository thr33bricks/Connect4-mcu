#include "logic_game.h"

#include <stdio.h>

#include "leds.h"
#include "music.h"
#include "logic_misc.h"
#include "rotary_encoder.h"

#include "page_instr.h"
#include "page_menu.h"
#include "page_game.h"
#include "page_game_over.h"

// 'o' => empty, 'y' => yellow, 'r' => red, 'g' => selection
char board[6][7];

// Game variables
uint8_t currentPlayer; // 0 for yellow, 1 for red
uint8_t scoreYellow = 0;
uint8_t scoreRed = 0;
uint8_t winner;
uint8_t gameOver;


void initGame() {
    resetcurrPosX();
    resetRot(ROT_RED);
    setPlayerLedOff();
    initBoard();
    gameOver = 0;
}

void initBoard(){
    for (uint8_t i = 0; i < 6; ++i){
        for (uint8_t j = 0; j < 7; ++j){
            board[i][j] = 'o';
        }
    }
}

GameState handleMenu(){
    displayMenu();

    // Start game
    if (wasPressed(ROT_RED)){
        playClickSound();
        drawPlayButtonAnimation();
        initGame();
        return STATE_PLAYING;
    }

    // Instructions
    if (wasPressed(ROT_GREEN)){
        playClickSound();
        drawInstrButtonAnimation();
        resetSupLineDisplayed(); // Reset scroll
        resetRot(ROT_RED); // Reset rotary encoder
        return STATE_INSTRUCTIONS;
    }

    return STATE_MENU;
}

GameState handleInstructions(){
    displayInstructions();

    // MAIN MENU
    if (wasPressed(ROT_BLUE)){
        playClickSound();
        drawHomeInstrBtnAnimation();
        return STATE_MENU;
    }

    return STATE_INSTRUCTIONS;
}

GameState handleGame(uint8_t grad){
    setPlayerLed(currentPlayer);
    currentSelection(board); // Check rotary encoder
    displayGame(board, scoreYellow, scoreRed, grad);
    clearCurrSel(board);

    // red button for placing disc
    if (wasPressed(ROT_RED)){
        // Play click sound if a valid move
        playClickSound();

        if(placeDisc(board, currentPlayer == 0 ? 'y' : 'r'))
            currentPlayer = !currentPlayer;
        
        uint8_t over = isGameOver(board);
        if(over != 0){
            if (over == 'y') {
                printf("Yellow player wins!\n");
                currentPlayer = !currentPlayer;
                winner = 'y';
                scoreYellow++;
            }
            if (over == 'r') {
                printf("Red player wins!\n");
                currentPlayer = !currentPlayer;
                winner = 'r';
                scoreRed++;
            }
            if (over == 't') {
                printf("Game is a tie!\n");
                winner = 't';
            }

            return STATE_GAME_OVER;
        }
    }

    // MAIN MENU
    if (wasPressed(ROT_BLUE)){
        playClickSound();
        drawHomeButtonAnimation();
        setPlayerLedOff();
        return STATE_MENU;
    }

    return STATE_PLAYING;
}

GameState handleGameOver(){
    displayGameOver(winner, scoreYellow, scoreRed);

    if(gameOver == 0){
        if(winner == 'y')
            setPlayerLed(0);
        else if(winner == 'r')
            setPlayerLed(1);

        playKorobeiniki();
        gameOverLEDS();

        gameOver = 1;
    }

    // MAIN MENU
    if (wasPressed(ROT_BLUE)){
        playClickSound();
        drawMenuButtonAnimation();
        setPlayerLedOff();
        return STATE_MENU;
    }

    // PLAY AGAIN
    if (wasPressed(ROT_RED)){
        playClickSound();
        drawPlAgainButtonAnimation();
        initGame();
        return STATE_PLAYING;
    }

    return STATE_GAME_OVER;
}
