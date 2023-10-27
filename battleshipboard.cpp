// Name:       Cheung Hop Cheung
// Student ID: 1155191857
// Email:      1155191857@link.cuhk.edu.hk

#include <iostream>
#include <iomanip>
#include <cctype>
#include "battleshipboard.h"
/* You may add extra standard library headers if you see fit */

using namespace std;

// Return a 5-letter string showing which ships of the specified fleet have sunk
string fleetStatus(Fleet fleet) {
    string result = "";
    for (int i = 0; i < 5; i++) {
        if (fleet.alive[i] > 0) {
            result += SHIP_TYPE[i][0];
        } else {
            result += HIT;
        }
    }
    return result;
}

// Print the status string of each fleet
void printStatus(Fleet fleet1, Fleet fleet2) {
    cout << setw(N*2 + 2) << left;
    cout << fleet1.name + " Fleet: " + fleetStatus(fleet1) << "  ";
    cout << setw(N*2 + 2) << left;
    cout << fleet2.name + " Fleet: " + fleetStatus(fleet2) << endl;
}

// Print the user and computer game boards side by side
void printBoards(char board1[][N], char board2[][N], bool gameMode) {
    cout << setw(N*2 + 2) << left << "Enemy Ocean" << "  "
         << setw(N*2 + 2) << left << "Your Ocean" << endl << right;
    
    // print column headers for both game boards
    for (int i = 0; i < 2; i++) {
        cout << string(2 + i*2, ' ');
        for (int j = 0; j < N; j++)
            cout << setw(2) << char('A' + j);
    }
    cout << endl;
    for (int row = 1; row <= N; row ++) {
        if (row < 10) {
            cout << " " << row;
        } else {
            cout << row;
        }
        for (int col = 1; col <= N; col++) {
            if (gameMode == 1) {
                if (board1[row - 1][col -1] != HIT || board1[row - 1][col -1] != MISS) {
                    cout << " " << BLANK;
                } else {
                    cout << " " << board1[row - 1][col - 1];
                }
            } else {
                cout << " " << board1[row - 1][col - 1];
            }
        }
        cout << "  ";
        if (row < 10) {
            cout << " " << row;
        } else {
            cout << row;
        }
        for (int col = 1; col <= N; col++) {
            cout << " " << board2[row - 1][col - 1];
        }
        cout << "\n";
    }
    // print row indexes and board content for both game boards
    // TODO: Add your code
}

// Check if the specified location (y, x) is within the board
bool isValidCell(int y, int x) {
    // TODO: Add your code
    return true;
}

// Check if a shoot location (y, x) is valid
bool isValidShoot(char board[][N], int y, int x) {
    // TODO: Add your code
    return true;
}

// Convert ship letter to its index in the ship type array
int indexOf(char ship) {
    // TODO: Add your code
    return 1;
}

// Carry out a shot on the specified board at location (y, x)
bool shoot(char board[][N], int y, int x, Fleet* fleet) {
    // TODO: Add your code
    return true;
}

// Get location (y, x) from the user via console input
bool getCellFromConsole(int& y, int& x) {
    char col; int row;
    cin >> col >> row;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    // TODO: Add your code
    
    return true;
}

// Get a random location (y, x) within board size
void getRandomCell(int& y, int& x) {
    y = rand() % N;
    x = rand() % N;
}

// Prompt the user for shoot location (y, x)
bool getHumanMove(int& y, int& x) {
    cout << "Enter attack location: ";
    return getCellFromConsole(y, x);
}

// Get shoot location (y, x) by the computer player's strategy
bool getComputerMove(char board[][N], int& y, int& x) {
    // try to shoot neighborhood of an existing hit first
    const int TRIALS = 1000;
    int dy[] = { -1,  0,  1,  0 };  // deltas for getting the cell at 
    int dx[] = {  0,  1,  0, -1 };  // North, East, South, West around (y, x)
    for (int t = 0; t < TRIALS; t++) {
        int i, j;
        getRandomCell(i, j);
        if (board[i][j] == HIT) {
            int st = rand() % 4;
            for (int k = 0; k < 4; k++) {
                int r = (st + k) % 4;  // random start in dy, dx
                if (isValidCell(i + dy[r], j + dx[r]) && 
                    board[i + dy[r]][j + dx[r]] != HIT && 
                    board[i + dy[r]][j + dx[r]] != MISS) {
                    y = i + dy[r]; x = j + dx[r];
                    return true;
                }
            }
        }
    }

    // shoot at a random location
    getRandomCell(y, x);
    return true;
}

// Place ship on board in specified orientation (vertical or horizontal)
bool placeShip(char board[][N], int y, int x, char ship, bool vertical = false) {
    return true;
    // TODO: Add your code
}

// Randomly place all ships on board
void randomlyPlaceShips(char board[][N]) {
    for (int k = 0; k < 5; k++) {
        char ship = SHIP_TYPE[k][0];
        while (true) {
            int y, x;
            bool vertical = bool(rand() % 2);
            getRandomCell(y, x);
            if (placeShip(board, y, x, ship, vertical))
                break;
        }
    }
}

// Manually place all ships on board
void manuallyPlaceShips(char board[][N]) {
    // TODO: Add your code
}

int main() {
    char myBoard[N][N] = { ' ' }, enBoard[N][N] = { ' ' };
    fill(myBoard[0] + 0, myBoard[N-1] + N, BLANK);
    fill(enBoard[0] + 0, enBoard[N-1] + N, BLANK);
    Fleet Test = {"Enemy", {5, 4, 0, 3, 2}};
    printBoards(myBoard, enBoard, 0);
}