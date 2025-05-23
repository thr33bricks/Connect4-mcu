#include "logic_game.h"
#include "lcd.h"
#include "rotary_encoder.h"
#include <stdio.h>

// 'o' => empty
// 'y' => yellow
// 'r' => red
// 'g' => selection
char board[6][7];

// Game variables
uint8_t lastPosX;
uint8_t currPosX;
uint8_t currPosY;
uint8_t currentPlayer; // 0 for yellow, 1 for red
uint8_t scoreYellow;
uint8_t scoreRed;

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
//====== DISPLAY MENU ============//
void drawConnect4Title(){
    char title[10];
    sprintf(title, "Connect 4");
    drawText(4, 100, 20, title, RED, 2);
}

void drawPlayButton(){
    drawRect (100, 200, 200, 50, GREEN);
}

void drawInstructionButton(){
    drawRect (100, 120, 200, 50, RED);
}

void displayMenu(){
    drawBackground(WHITE);
    drawConnect4Title();
    drawPlayButton();
    drawInstructionButton();
    draw();
}


//====== DISPLAY INSTRUCTIONS ============//
void displayInstructions(){
    drawInstructionsTitle();
    displayLongText();
    drawInstructionMenuButton();
}

void drawInstructionsTitle(){
    drawText(2, 20, 10, "Instructions", GREEN, 1);
}

void displayLongText(){
    const char *instructions_text[] = {
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
    const int instruction_lines = sizeof(instructions_text) / sizeof(instructions_text[0]);
    
    static int scroll_offset = 0; // scroll position
    int max_visible_lines = 6;
    int y_start = 60;
    int line_spacing = 20;

    // Ajust the scroll
    int scroll_input = getRotGreen();
    scroll_offset = scroll_input;

    // Limit the scroll
    if (scroll_offset < 0) scroll_offset = 0;
    if (scroll_offset > instruction_lines - max_visible_lines)
        scroll_offset = instruction_lines - max_visible_lines;

    // Display visible instructions lines
    for (int i = 0; i < max_visible_lines; ++i) {
        int line_index = scroll_offset + i;
        if (line_index < instruction_lines) {
            drawText(4, y_start + i * line_spacing, 16, instructions_text[line_index], BLACK, 1);
        }
    }
}

void drawInstructionMenuButton(){
    
}

// =========== DISPLAY GAME ========= //
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
    drawBoard();
    drawScore();
    draw();
}
//====== DISPLAY GAME OVER ============//
void displayGameOver(){

}

//======= GAME STATES ============//
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
    currentSelection(); // Rotary encoder
    displayGame();

    // check red button (to select the right column)
    if (wasPressed(BTN_RED)){
        printf("Red button pressed\n");
        if (board[currPosY][currPosX] == 'o'){
            board[currPosY][currPosX] = currentPlayer == 0 ? 'y' : 'r';
            currentPlayer = !currentPlayer;
        }

        // Use the isGameOver(char color) function
        if (isGameOver('y')) {
            printf("Yellow player wins!\n");
            return STATE_GAME_OVER;
        }
        if (isGameOver('r')) {
            printf("Red player wins!\n");
            return STATE_GAME_OVER;
        }
    }

    // check blue button (to go back to the main menu)
    if (wasPressed(BTN_BLUE)){
        printf("Blue button pressed\n");
        // Go back to the main menu
        return STATE_MENU;
    }

    clearCurrSel();

    return STATE_PLAYING;
}
GameState handleGameOver(){
    // Handle interruptions (Blue and green button)
    displayGameOver();

    return STATE_GAME_OVER;
}
 
int isGameOver(char color) {
    int lignes = 6;
    int rows = 7;

    // Horizontal checking
    for (int i = 0; i < lignes; i++) {
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
    for (int i = 0; i < lignes - 3; i++) {
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
    for (int i = 0; i < lignes - 3; i++) {
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
    for (int i = 3; i < lignes; i++) {
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
