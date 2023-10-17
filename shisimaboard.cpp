// Name:       Cheung Hop Cheung
// Student ID: 1155191857
// Email:      1155191857@link.cuhk.edu.hk

#include "shisimaboard.h"
#include <iostream>
using namespace std;

int Power(int x, int y) {
    if (y == 0) {
        return 1;
    }
    int result = x;
    for (int i = 1; i < y; i++) {
        
        result *= x;
    }
    return result;
}

int adj(int pos1, int pos2) {
    if (pos2 == 5 || pos1 == 5) {
        return true;
    }
    switch(pos1){
        case 0:
            if(pos2 == 2 || pos2 == 4) {
                return true;
            }
        case 1:
            if(pos2 == 1 || pos2 == 3) {
                return true;
            }
        case 3:
            if(pos2 == 2 || pos2 == 6) {
                return true;
            }
        case 4:
            if(pos2 == 1 || pos2 == 7) {
                return true;
            }
        case 6:
            if(pos2 == 3 || pos2 == 9) {
                return true;
            }
        case 7:
            if(pos2 == 4 || pos2 == 8) {
                return true;
            }
        case 8:
            if(pos2 == 7 || pos2 == 9) {
                return true;
            }
        case 9:
            if(pos2 == 8 || pos2 == 6) {
                return true;
            }
    }
    return false;
}

/* Returns the state of position pos of the game board. */
int boardState(int board, int pos) {
    int multiplier = 1, value;
    // for (int i = 1; i < (10 - pos); i++) {
    //     multiplier = multiplier * 10;
    // }
    multiplier = Power(10, (9 - pos));
    if (multiplier == 0) {
        return (board % 10);
    }
    return(board / multiplier % 10);
}

/* Prints the board to the screen. DO NOT MODIFY! */
void printBoard(int board) {
    cout << "  " << boardState(board, 1) << "-" << boardState(board, 2) << "-" << boardState(board, 3) << endl;
    cout << " / \\|/ \\" << endl;
    cout << boardState(board, 4) << "---" << boardState(board, 5) << "---" << boardState(board, 6) << endl;
    cout << " \\ /|\\ /" << endl;
    cout << "  " << boardState(board, 7) << "-" << boardState(board, 8) << "-" << boardState(board, 9) << endl;
}

/* Performs the task of player p moving a piece from position pos1 to position
   pos2 of board. */
bool movePiece(int &board, int pos1, int pos2, int p) {
    if(pos1 < 1 || pos1 > 9 || pos2 < 1 || pos2 > 9) {
        return false;
    }
    if(boardState(board, pos2) != 0 || boardState(board, pos1) != p) {
        return false;
    }
    if(adj(pos1, pos2) == false) {
        return false;
    }
    board -= boardState(board, pos1) * Power(10, (9 - pos1));
    board += p * Power(10, (9-pos2));
    cout << board;
    return true;
}

/* Checks if any player has formed a line of three pieces crossing the middle
   of the board. */
int formLine(int board) {

    int dt = boardState(board, 5);
    for (int i = 1; i < 5; i++) {
        if (dt == boardState(board, i) && dt == boardState(board, 10 - i)) {
            return dt;
        }
    }

    return 0;
}

/* You may write a main() in this file for debugging purpose, but it must be
   removed or commented in your submitted version. */
int main() {
    int board = 110001222;
    cout << formLine(board);
}