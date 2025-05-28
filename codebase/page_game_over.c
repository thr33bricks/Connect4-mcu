#include "page_game_over.h"

#include <stdio.h>

#include "mzapo_parlcd.h"
#include "settings.h"
#include "lcd.h"

// GAME OVER BUTTONS Locations
uint16_t menuBtnX = 310;
uint16_t menuBtnY = 220;
uint16_t plAgainBtnX = 60;
uint16_t plAgainBtnY = 220;


void drawGameOverTitle(uint8_t winner){
    char title[7];
    if(winner == 'y')
        sprintf(title, "Yellow");
    else if (winner == 'r')
        sprintf(title, "Red");
    else
        sprintf(title, "Tie!");

    if(winner == 'y'){
        setShadow(2, BLACK);
        drawText(4, 50, 20, title, YELLOW, 1);
        setShadow(2, LIGHT_GRAY);
        drawText(4, 280, 20, "wins!", BLACK, 1);
    } else if (winner == 'r'){
        setShadow(2, BLACK);
        drawText(4, 100, 20, title, RED, 1);
        setShadow(2, LIGHT_GRAY);
        drawText(4, 220, 20, "wins!", BLACK, 1);
    } else{
        setShadow(2, BLACK);
        drawText(4, 180, 20, title, BLUE, 1);
    }
}

// x,y = 110, 120
void drawMenuButton(uint16_t x, uint16_t y){
    char title[10];
    sprintf(title, "MENU");
    drawRect (x+1, y+1, 107, 50, BLACK);
    drawRect (x+1, y+1, 105, 48, BLUE);
    drawRect (x, y, 107, 50, BLUE);
    drawText(2, x+10, y+10, title, BLUE, 2);
}

// x,y = 110, 200
void drawPlAgainButton(uint16_t x, uint16_t y){
    char title[20];
    sprintf(title, "PLAY AGAIN");
    drawRect (x+1, y+1, 218, 50, BLACK);
    drawRect (x+1, y+1, 216, 48, RED);
    drawRect (x, y, 218, 50, RED);
    drawText(2, x+10, y+10, title, RED, 2);
}

void drawPlAgainButtonAnimation(){
    for (size_t i = 0; i < ANIM_CNT; ++i){
        drawRect (plAgainBtnX-i, plAgainBtnY-i, 218+i*2, 50+i*2, RED);
        draw();
        parlcd_delay(ANIM_DELAY);
    }
}

void drawMenuButtonAnimation(){
    for (size_t i = 0; i < ANIM_CNT; ++i){
        drawRect (menuBtnX-i, menuBtnY-i, 107+i*2, 50+i*2, BLUE);
        draw();
        parlcd_delay(ANIM_DELAY);
    }
}

void displayGameOver(uint8_t winner, uint8_t scoreYellow, uint8_t scoreRed){
    drawBackground(WHITE);
    drawGameOverTitle(winner);
    setShadow(1, LIGHT_GRAY);
    drawScore(130, 120, scoreYellow, scoreRed);
    setShadow(2, BLACK);
    drawMenuButton(menuBtnX, menuBtnY);
    drawPlAgainButton(plAgainBtnX, plAgainBtnY);
    draw();
}

void drawScore(uint16_t x, uint16_t y, uint8_t scoreYellow, uint8_t scoreRed){
    char score[20];
    sprintf(score, "Score: %d-%d", scoreYellow, scoreRed);
    drawText(2, x, y, score, BLACK, 1);
}