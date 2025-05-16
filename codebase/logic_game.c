#include "logic_game.h"
#include "lcd.h"
#include "rotary_encoder.h"
#include <stdio.h>

void initBoard(){
    for (uint8_t i = 0; i < 6; ++i){
        for (uint8_t j = 0; j < 7; ++j){
            board[i][j] = 'o';
        }
    }
}

void initGame() {
    initEncoders();
    initLcd();
    initBoard();

    currPosX = 0;
    lastPosX = 0;
    currPosY = 0;
    currentPlayer = 0;
    scoreYellow = 0;
    scoreRed = 0;
}

void startGame(){

}

void displayMenu(){
    
}

void displayInstructions(){

}

void currentSelection(){
    int rot = getRotRed();
    currPosX = rot % 7;

    for (currPosY = 5; currPosY >= 0 ; --currPosY){
        if(board[currPosY][currPosX] == 'o')
            break;
    }

    if(board[currPosY][currPosX] == 'o')
        board[currPosY][currPosX] = 'g';
}

void clearCurrSel(){
    if(board[currPosY][currPosX] == 'g'){
        board[currPosY][currPosX] = 'o';
    }
}

void drawBoard(){
    uint8_t boardX = 86;
    uint8_t boardY = 45;
    uint8_t holeSize = 20;
    uint8_t space = 2;

    // Draw background and blue board
    drawBackground(WHITE);
    drawFillRect(boardX, boardY, 480-2*boardX, 265, BLUE);

    //cut corners
    drawFillRect(boardX, boardY, 20, 20, WHITE);
    drawFillRect(480-boardX-20, boardY, 20, 20, WHITE);
    drawFillRect(boardX, boardY+265-20, 20, 20, WHITE);
    drawFillRect(480-boardX-20, boardY+265-20, 20, 20, WHITE);
    drawFillCircle(boardX+20, boardY+20, 20, BLUE);
    drawFillCircle(480-boardX-21, boardY+20, 20, BLUE);
    drawFillCircle(boardX+20, 265+24, 20, BLUE);
    drawFillCircle(480-boardX-21, 265+24, 20, BLUE);
    
    // Draw the board
    for (uint8_t i = 0; i < 6; ++i){
        for (uint8_t j = 0; j < 7; ++j){
            uint16_t color = WHITE;
            if(board[i][j] == 'y')
                color = YELLOW;
            else if(board[i][j] == 'r')
                color = RED;
            else if(board[i][j] == 'g')
                color = GREEN;
            
            drawFillCircle(boardX+space+holeSize+5 + j*(space+2*holeSize), boardY+space+holeSize+5 + i*(space+2*holeSize), holeSize, BLACK);
            drawFillCircle(boardX+space+holeSize+5 + j*(space+2*holeSize), boardY+space+holeSize+5 + i*(space+2*holeSize), holeSize-2, color);
        }
    }
}

void drawScore(){
    char score[20];
    sprintf(score, "Score: %d-%d", scoreYellow, scoreRed);
    drawText(2, 20, 10, score, BLACK, 1);
}

void displayGame(){
    currentSelection();
    drawBoard();
    drawScore();
    draw();

    clearCurrSel();
}

void displayGameOver(){

}

GameState handleMenu(){
    displayMenu();
    return STATE_MENU;
}
GameState handleInstructions(){
    // Handle interruptions (Blue button + green rotary encoder)
    displayInstructions();

    return STATE_INSTRUCTIONS;
}
GameState handleGame(){
    // Handle interruptions (Blue and red button + red rotary encoder)
    displayGame();

    return STATE_PLAYING;
}
GameState handleGameOver(){
    // Handle interruptions (Blue and green button)
    displayGameOver();

    return STATE_GAME_OVER;
}


