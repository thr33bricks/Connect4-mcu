#include "page_instr.h"

#include "rotary_encoder.h"
#include "mzapo_parlcd.h"
#include "settings.h"
#include "lcd.h"

// INSTRUCTIONS BUTTONS Locations
#define homeInstrBtnX 380
#define homeInstrBtnY 275

// Lines of text
#define totalInstructionLines 29
#define maxLinesDisplayed 7
#define maxSupLine (totalInstructionLines - maxLinesDisplayed - 1)

uint8_t supLineDisplayed = 0;


void resetSupLineDisplayed(){
    supLineDisplayed = 0;
}

void greenTextPosition(){
    uint8_t rot = getRotDir(ROT_RED);
    supLineDisplayed = supLineDisplayed + ((rot == 'l') ? -1 : ((rot == 'r') ? 1 : 0));

    if(supLineDisplayed < 0)
        supLineDisplayed = 0;
    else if(supLineDisplayed > maxSupLine)
        supLineDisplayed = maxSupLine;
}

void drawHomeInstr(uint16_t x, uint16_t y, uint8_t shadow){
    if(shadow)
        drawFillCircle(x+10, y+7, 24, BLACK); // shadow
    drawFillCircle(x+10, y+5, 24, BLUE);
    drawFillCircle(x+10, y+5, 22, LIGHT_GREEN);

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

void drawHomeInstrBtnAnimation(){
    for (uint8_t i = 0; i < ANIM_CNT; ++i){
        drawFillCircle(homeInstrBtnX+10, homeInstrBtnY+5, 24+i, BLUE);
        drawHomeInstr(homeInstrBtnX, homeInstrBtnY, 0);
        draw();
        parlcd_delay(ANIM_DELAY);
    }
}

void displayInstructions(){
    drawBackground(LIGHT_GREEN);
    setShadow(1, LIGHT_GRAY);
    greenTextPosition();
    displayScroll();
    
    displayLongText();
    if (supLineDisplayed == maxSupLine)
        drawHomeInstr(homeInstrBtnX, homeInstrBtnY, 1);

    draw();
}

void displayScroll(){
    // Top triangle
    drawTriangle(469, 1, 460, 20, 478, 20, DARK_GREEN);
    drawTriangle(469, 2, 461, 19, 477, 19, DARK_GREEN);
    // Bottom triangle
    drawTriangle(469, 318, 460, 299, 478, 299, DARK_GREEN);
    drawTriangle(469, 319, 461, 300, 477, 300, DARK_GREEN);

    drawLine(468, 20, 468, 299, DARK_GREEN);
    drawLine(469, 20, 469, 299, DARK_GREEN);

    //supLineDisplayed, maxSupLine

    uint16_t yOffset = 243 * ((double)supLineDisplayed/(double)maxSupLine);

    drawFillRect(464, 24+yOffset, 13, 30, BLACK);
    drawFillRect(463, 23+yOffset, 13, 30, DARK_GREEN);
}

void displayLongText(){
    const char *instructions_text[] = {
        "INSTRUCTIONS",
        "Welcome to Connect 4!",
        "",
        "This is a two-player",
        "game. Players take",
        "turns dropping",
        "colored tokens into",
        "a grid.",
        "",
        "Goal: align 4 of your",
        "tokens horizontally,",
        "vertically, or",
        "diagonally before",
        "your opponent.",
        "",
        "Controls:",
        "- Use the red knob",
        "  to move the token",
        "  left/right.",
        "- Press to drop your",
        "  token.",
        "- Press the blue",
        "  knob to go to main",
        "  menu.",
        " ",
        "Good luck and have",
        "fun!",
        "",
        "",
    };

    uint8_t x=20;
    uint8_t y=10;
    for (uint8_t i=supLineDisplayed; i<supLineDisplayed+maxLinesDisplayed;i++){
        drawText(2, x, y, (char*)instructions_text[i], BLACK, 1);
        y+=40;
    }
}
