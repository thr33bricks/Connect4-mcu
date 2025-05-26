#include "page_game.h"

#include <stdio.h>

#include "settings.h"
#include "lcd.h"
#include "rotary_encoder.h"
#include "logic_misc.h"
#include "mzapo_parlcd.h"
#include "page_game_over.h"

// GAME BUTTONS Locations
#define homeBtnX 425
#define homeBtnY 275

int8_t lastPosX = 8;
int8_t currPosX = 0;
int8_t currPosY;

uint8_t gameStarted = 0;


void searchValidPosX(char board[6][7], uint8_t rot){
    int8_t delta = (rot == 'l') ? -1 : 1;

    while(1){
        printf("delta: %d\n", delta);
        printf("currPosX: %d, currPosY: %d\n", currPosX, currPosY);
        for (currPosY = 5; currPosY >= 0 ; --currPosY){
            if(board[currPosY][currPosX] == 'o' || currPosY == -1)
                break;
        }

        // No valid position found
        if(currPosY == -1){
            currPosX += delta;
            if(currPosX < 0)
                currPosX = 6;
            else if(currPosX > 6)
                currPosX = 0;
        } else {
            break; // Valid position found
        }
    }
}

void currentSelection(char board[6][7]){
    uint8_t rot = getRotDir(ROT_RED);
    if(rot == 'l'){
        if(currPosX > 0)
            currPosX--;
        else
            currPosX = 6;
    } else if(rot == 'r'){
        if(currPosX < 6)
            currPosX++;
        else
            currPosX = 0;
    }

    searchValidPosX(board, rot);

    if(lastPosX != currPosX){
        if(gameStarted == 0){
            gameStarted = 1;
        }else {
            playScrollSound();
        }
        lastPosX = currPosX;
    }

    if(board[currPosY][currPosX] == 'o')
        board[currPosY][currPosX] = 'g';
}

void clearCurrSel(char board[6][7]){
    if(currPosY == -1)
        return;
    if(board[currPosY][currPosX] == 'g'){
        board[currPosY][currPosX] = 'o';
    }
}

uint8_t placeDisc(char board[6][7], uint8_t color){
    if (board[currPosY][currPosX] == 'o'){
        board[currPosY][currPosX] = color;
        return 1;
    }
    return 0;
}

void drawBoard(char board[6][7], uint8_t grad){
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

    // Shadow
    drawFillCircle(boardX+24, 265+28, 20, BLACK); // left corner
    drawFillRect(boardX+20, boardY+265-20, 26, 20, BLUE); 
    drawFillRect(boardX+30, boardY+265, 260, 3, BLACK); // bottom
    drawFillCircle(480-boardX-18, 265+27, 20, BLACK); // right corner
    drawFillRect(480-boardX-21, 265, 20, 20, BLUE);
    drawFillRect(480-boardX-35, 265+24, 20, 20, BLUE);
    drawFillRect(480-boardX, boardY+20, 3, 222, BLACK);
    drawFillCircle(480-boardX-17, boardY+24, 20, BLACK); // top corner
    drawFillRect(480-boardX-26, boardY+24, 26, 20, BLUE); 

    // rounded corners
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
            else if(board[i][j] == 'g'){
                color = (grad << 5);
            }
            
            drawFillCircle(boardX+space+holeSize+5 + j*(space+2*holeSize), boardY+space+holeSize+5 + i*(space+2*holeSize), holeSize, BLACK);
            drawFillCircle(boardX+space+holeSize+5 + j*(space+2*holeSize), boardY+space+holeSize+5 + i*(space+2*holeSize), holeSize-2, color);
        }
    }
}

void drawHome(uint16_t x, uint16_t y, uint8_t shadow){
    if(shadow)
        drawFillCircle(x+10, y+7, 24, BLACK); // shadow
    drawFillCircle(x+10, y+5, 24, BLUE);
    drawFillCircle(x+10, y+5, 22, WHITE);

    // House base (20x20 square)
    drawLine(x+13, y+20, x+20, y+20, BLUE); // Bottom
    drawLine(x, y+20, x+7, y+20, BLUE);     // Bottom
    drawLine(x+20, y+20, x+20, y, BLUE);    // Right
    drawLine(x+25, y, x+20, y, BLUE);       // Top
    drawLine(x, y, x-5, y, BLUE);           // Top
    drawLine(x, y, x, y+20, BLUE);          // Left

    // Roof (wider triangle)
    drawLine(x-5, y, x+10, y-12, BLUE);   // Left roof slope
    drawLine(x+10, y-12, x+25, y, BLUE);  // Right roof slope

    // Door (6x10 rectangle, centered)
    drawLine(x+13, y+20, x+13, y+10, BLUE); // Right
    drawLine(x+13, y+10, x+7, y+10, BLUE);  // Top
    drawLine(x+7, y+10, x+7, y+20, BLUE);   // Left
}

void displayGame(char board[6][7], uint8_t scoreYellow, uint8_t scoreRed, uint8_t grad){
    drawBoard(board, grad);
    setShadow(1, LIGHT_GRAY);
    drawScore(20, 10, scoreYellow, scoreRed);
    drawHome(homeBtnX, homeBtnY, 1);
    draw();
}

void drawHomeButtonAnimation(){
    for (size_t i = 0; i < ANIM_CNT; ++i){
        drawFillCircle(homeBtnX+10, homeBtnY+5, 24+i, BLUE);
        drawHome(homeBtnX, homeBtnY, 0);
        draw();
        parlcd_delay(ANIM_DELAY);
    }
}
