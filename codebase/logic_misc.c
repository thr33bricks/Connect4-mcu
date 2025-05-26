#include "logic_misc.h"

#include "speaker.h"


uint8_t isGameOver(char board[6][7]){
    if(checkWinner(board, 'y'))
        return 'y';
    if(checkWinner(board, 'r'))
        return 'r';
    if(checkTie(board))
        return 't';

    return 0;
}

uint8_t checkTie(char board[6][7]){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 'o') {
                return 0;
            }
        }
    }
    return 1;
}

uint8_t checkWinner(char board[6][7], char color){
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