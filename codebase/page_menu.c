#include "page_menu.h"

#include <stdio.h>

#include "mzapo_parlcd.h"
#include "settings.h"
#include "lcd.h"

// MENU BUTTONS Locations
uint16_t playBtnX = 185;
uint16_t playBtnY = 120;
uint16_t instructionBtnX = 110;
uint16_t instructionBtnY = 200;


void drawConnect4Title(){
    char title[10];
    sprintf(title, "Connect 4");
    drawText(4, 100, 20, title, RED, 2);
}

// x,y = 110, 120
void drawPlayButton(uint16_t x, uint16_t y){
    char title[10];
    sprintf(title, "PLAY");
    drawRect(x+1, y+1, 105, 50, BLACK); // sh
    drawRect (x, y, 105, 50, RED);
    drawRect (x+1, y+1, 103, 48, RED);
    drawText(2, x+10, y+10, title, RED, 2);
}

// x,y = 110, 200
void drawInstructionButton(uint16_t x, uint16_t y){
    char title[20];
    sprintf(title, "INSTRUCTIONS");
    drawRect (x+1, y+1, 265, 50, BLACK); // sh
    drawRect (x, y, 265, 50, GREEN);
    drawRect (x+1, y+1, 263, 48, GREEN);
    drawText(2, x+10, y+10, title, GREEN, 2);
}

void drawPlayButtonAnimation(){
    for (size_t i = 0; i < ANIM_CNT; ++i){
        drawRect (playBtnX-i, playBtnY-i, 105+i*2, 50+i*2, RED);
        draw();
        parlcd_delay(ANIM_DELAY);
    }
}

void drawInstrButtonAnimation(){
    for (size_t i = 0; i < ANIM_CNT; ++i){
        drawRect (instructionBtnX-i, instructionBtnY-i, 265+i*2, 50+i*2, GREEN);
        draw();
        parlcd_delay(ANIM_DELAY);
    }
}

void displayMenu(){
    drawBackground(WHITE);
    setShadow(2, BLACK);
    drawConnect4Title();
    drawPlayButton(playBtnX, playBtnY);
    drawInstructionButton(instructionBtnX, instructionBtnY);
    draw();
}