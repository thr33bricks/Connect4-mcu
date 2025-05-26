#include "logic_game.h"
#include "lcd.h"
#include "rotary_encoder.h"
#include "speaker.h"
#include "leds.h"
#include "mzapo_parlcd.h"
#include <stdio.h>

#define ANIM_CNT 6
#define ANIM_DELAY 5

// 'o' => empty
// 'y' => yellow
// 'r' => red
// 'g' => selection
char board[6][7];

// Game variables
uint8_t lastPosX = 8;
uint8_t currPosX = 0;
int8_t currPosY;
uint8_t currentPlayer; // 0 for yellow, 1 for red
uint8_t scoreYellow = 0;
uint8_t scoreRed = 0;
uint8_t winner;
uint8_t gameOver;

// MENU BUTTONS Locations
uint16_t playBtnX = 185;
uint16_t playBtnY = 120;
uint16_t instructionBtnX = 110;
uint16_t instructionBtnY = 200;

// GAME OVER BUTTONS Locations
uint16_t menuBtnX = 60;
uint16_t menuBtnY = 220;
uint16_t plAgainBtnX = 200;
uint16_t plAgainBtnY = 220;

// GAME BUTTONS Locations
uint16_t homeBtnX = 425;
uint16_t homeBtnY = 275;


void initBoard(){
    for (uint8_t i = 0; i < 6; ++i){
        for (uint8_t j = 0; j < 7; ++j){
            board[i][j] = 'o';
        }
    }
}

void initGame() {
    initBoard();
    gameOver = 1;
}

//====== DISPLAY MENU ============//
void drawConnect4Title(){
    char title[10];
    sprintf(title, "Connect 4");
    drawText(4, 100, 20, title, RED, 2);
}

// x,y = 110, 120
void drawPlayButton(uint16_t x, uint16_t y){
    char title[10];
    sprintf(title, "PLAY");
    drawRect (x, y, 105, 50, RED);
    drawText(2, x+10, y+10, title, RED, 2);
}

// x,y = 110, 200
void drawInstructionButton(uint16_t x, uint16_t y){
    char title[20];
    sprintf(title, "INSTRUCTIONS");
    drawRect (x, y, 265, 50, GREEN);
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
    drawConnect4Title();
    drawPlayButton(playBtnX, playBtnY);
    drawInstructionButton(instructionBtnX, instructionBtnY);
    draw();
}

//====== DISPLAY INSTRUCTIONS ============//
void displayInstructions(){
    drawBackground(WHITE);
    int SupLineDisplayed =0;
    //int SupLineDisplayed = greenRotaryEncoderPosition(); 
    
    displayLongText(SupLineDisplayed);
    if (SupLineDisplayed == 13){
        drawHome(425, 275);
    }
}

int greenRotaryEncoderPosition(){   // TO DO ++++++++++++++++++++++++++++++
    int SupLineDisplayed; // Should be >=0 and <=13

    return SupLineDisplayed;
}

void displayLongText(int SupLineDisplayed){
    const char *instructions_text[] = {
        // 17 instructions lines
        "INSTRUCTIONS",
        "Welcome to Connect 4!",
        "",
        "This is a two-player game.",
        "Players take turns dropping",
        "colored tokens into a grid.",
        "",
        "Goal: align 4 of your tokens",
        "horizontally, vertically, or",
        "diagonally before your opponent.",
        "",
        "Controls:",
        "- Use the red encoder to move",
        "  the token left/right.",
        "- Press to drop your token.",
        "",
        "Good luck and have fun!"
    };
    // 5 lines are displayed 
    int x=20;
    int y=10;
    for (int i=SupLineDisplayed; i<SupLineDisplayed+5;i++){
        drawText(1, x, y, instructions_text[i], BLACK, 1);
        y+=40;
    }

}

// =========== DISPLAY GAME ========= //

void searchValidPosX(uint8_t rot){
    //if(rot == 0) return;
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

void currentSelection(){
    //int rot = getRotRed();
    //currPosX = rot % 7;

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

    searchValidPosX(rot);

    if(lastPosX != currPosX){
        if(gameOver == 1){
            gameOver = 0;
        }else {
            playScrollSound();
        }
        lastPosX = currPosX;
    }

    if(board[currPosY][currPosX] == 'o')
        board[currPosY][currPosX] = 'g';
}

void clearCurrSel(){
    if(currPosY == -1)
        return;
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

// x,y = 20, 10
void drawScore(uint16_t x, uint16_t y){
    char score[20];
    sprintf(score, "Score: %d-%d", scoreYellow, scoreRed);
    drawText(2, x, y, score, BLACK, 1);
}

void drawHome(uint16_t x, uint16_t y){
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

void displayGame(){
    drawBoard();
    drawScore(20, 10);
    drawHome(homeBtnX, homeBtnY);
    draw();
}

void drawHomeButtonAnimation(){
    for (size_t i = 0; i < ANIM_CNT; ++i){
        drawFillCircle(homeBtnX+10, homeBtnY+5, 24+i, BLUE);
        drawHome(homeBtnX, homeBtnY);
        draw();
        parlcd_delay(ANIM_DELAY);
    }
}

//====== DISPLAY GAME OVER ============//
void drawGameOverTitle(){
    char title[7];
    if(winner == 'y')
        sprintf(title, "Yellow");
    else if (winner == 'r')
        sprintf(title, "Red");
    else
        sprintf(title, "Tie!");

    if(winner == 'y'){
        drawText(4, 50, 20, title, YELLOW, 1);
        drawText(4, 280, 20, "wins!", BLACK, 1);
    } else if (winner == 'r'){
        drawText(4, 100, 20, title, RED, 1);
        drawText(4, 220, 20, "wins!", BLACK, 1);
    } else{
        drawText(4, 180, 20, title, BLUE, 1);
    }
}

// x,y = 110, 120
void drawMenuButton(uint16_t x, uint16_t y){
    char title[10];
    sprintf(title, "MENU");
    drawRect (x, y, 107, 50, BLUE);
    drawText(2, x+10, y+10, title, BLUE, 2);
}

// x,y = 110, 200
void drawPlAgainButton(uint16_t x, uint16_t y){
    char title[20];
    sprintf(title, "PLAY AGAIN");
    drawRect (x, y, 218, 50, GREEN);
    drawText(2, x+10, y+10, title, GREEN, 2);
}

void drawPlAgainButtonAnimation(){
    for (size_t i = 0; i < ANIM_CNT; ++i){
        drawRect (plAgainBtnX-i, plAgainBtnY-i, 218+i*2, 50+i*2, GREEN);
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

void displayGameOver(){
    drawBackground(WHITE);
    drawGameOverTitle();
    drawScore(130, 120);
    drawMenuButton(menuBtnX, menuBtnY);
    drawPlAgainButton(plAgainBtnX, plAgainBtnY);
    draw();
}

//======= CHECK GAME OVER ============//
uint8_t isGameOver(){
    if(checkWinner('y'))
        return 'y';
    if(checkWinner('r'))
        return 'r';
    if(checkTie())
        return 't';

    return 0;
}

uint8_t checkTie(){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 'o') {
                return 0;
            }
        }
    }
    return 1;
}

uint8_t checkWinner(char color){
    int lines = 6;
    int rows = 7;

    // Horizontal checking
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < rows - 3; j++) {
            if ((board[i][j] == color) &&
                (board[i][j+1] == color) &&
                (board[i][j+2] == color) &&
                (board[i][j+3] == color)) {
                return 1;
            }
        }
    }

    // Vertical checking
    for (int i = 0; i < lines - 3; i++) {
        for (int j = 0; j < rows; j++) {
            if ((board[i][j] == color) &&
                (board[i+1][j] == color) &&
                (board[i+2][j] == color) &&
                (board[i+3][j] == color)) {
                return 1;
            }
        }
    }

    // Diagonal checking ↘
    for (int i = 0; i < lines - 3; i++) {
        for (int j = 0; j < rows - 3; j++) {
            if ((board[i][j] == color) &&
                (board[i+1][j+1] == color) &&
                (board[i+2][j+2] == color) &&
                (board[i+3][j+3] == color)) {
                return 1;
            }
        }
    }

    // Diagonal checking ↗
    for (int i = 3; i < lines; i++) {
        for (int j = 0; j < rows - 3; j++) {
            if ((board[i][j] == color) &&
                (board[i-1][j+1] == color) &&
                (board[i-2][j+2] == color) &&
                (board[i-3][j+3] == color)) {
                return 1;
            }
        }
    }
    return 0;
}

void playScrollSound(){
    playTone(500, 20);
}

void playClickSound(){
    playTone(1000, 20);
}

void playKorobeiniki(){
    playTone(659, 150); // E5
    playTone(494, 150); // B4
    playTone(523, 150); // C5
    playTone(587, 150); // D5
    playTone(523, 150); // C5
    playTone(494, 150); // B4
    playTone(440, 150); // A4
    playTone(440, 150); // A4
    playTone(523, 150); // C5
    playTone(659, 150); // E5
    playTone(587, 150); // D5
    playTone(523, 150); // C5
    playTone(494, 450); // B4 long
}

//======= GAME STATES ============//
GameState handleMenu(){
    displayMenu();

    // Start game
    if (wasPressed(BTN_RED)){
        playClickSound();
        drawPlayButtonAnimation();
        initGame();
        return STATE_PLAYING;
    }

    // Instructions
    if (wasPressed(BTN_GREEN)){
        playClickSound();
        drawInstrButtonAnimation();
        return STATE_INSTRUCTIONS;
    }

    return STATE_MENU;
}

GameState handleInstructions(){
    displayInstructions();

    // MAIN MENU
    if (wasPressed(BTN_BLUE)){
        playClickSound();
        return STATE_MENU;
    }

    return STATE_INSTRUCTIONS;
}

GameState handleGame(){
    setPlayerLed(currentPlayer);
    currentSelection(); // Check rotary encoder
    displayGame();
    clearCurrSel();

    // red button for placing disc
    if (wasPressed(BTN_RED)){
        // Check if the column is full
        if(currPosY == -1)
            return STATE_PLAYING;

        // Play click sound if a valid move
        playClickSound();

        if (board[currPosY][currPosX] == 'o'){
            board[currPosY][currPosX] = currentPlayer == 0 ? 'y' : 'r';
            currentPlayer = !currentPlayer;
        }
        
        uint8_t over = isGameOver();
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
    if (wasPressed(BTN_BLUE)){
        playClickSound();
        drawHomeButtonAnimation();
        return STATE_MENU;
    }

    // TEST
    if (wasPressed(BTN_GREEN)){
        playClickSound();
    }

    return STATE_PLAYING;
}

GameState handleGameOver(){
    displayGameOver();

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
    if (wasPressed(BTN_BLUE)){
        playClickSound();
        drawMenuButtonAnimation();
        setPlayerLedOff();
        return STATE_MENU;
    }

    // PLAY AGAIN
    if (wasPressed(BTN_GREEN)){
        playClickSound();
        drawPlAgainButtonAnimation();
        setPlayerLedOff();
        initGame();
        return STATE_PLAYING;
    }

    return STATE_GAME_OVER;
}
