// Name:       Cheung Hop Cheung
// Student ID: 1155191857
// Email:      1155191857@link.cuhk.edu.hk

#include "shisimaboard.h"
#include <iostream>
using namespace std;

int main() {
    int board = 102102102;
    int player = 1, pos1, pos2, winner;
    printBoard(board);
    while(true) {
        cout << "Player " << player << " (from to): ";
        cin >> pos1 >> pos2;
        if (movePiece(board, pos1, pos2, player) != false) {
            printBoard(board);
            player = (player == 1 ? player = 2 : player = 1);
            winner = formLine(board);
            if (winner != 0) {
                cout << "Player " << winner << " wins!";
                break;
            }
        } else {
            cout << "Invalid. Try again!\n";
        }
    }
    
    
    return 0;
}