#include <iostream>
#include <string>
#include "RushHour.h"

using namespace std;

int findLen(string grid[], int car, int x, int y, bool vertical) {
    int len = 0;
    if (vertical) {
        while(grid[x][y] - '0' == car) {
            x += 1;
            len += 1;
        }
        return len;
    } else {
        while(grid[x][y] - '0' == car) {
            y += 1;
            len += 1;
        }
        return len;
    }
}

bool checkSpace(string grid[], int car, int len, int x, int y, bool vertical) {
    if (vertical) {
        for (int i = 0; i < len; i++) {
            if (grid[x + i][y] - '0' != car && grid[x + i][y]!= '.') {
                return false;
            }
        }
    } else {
        for (int i = 0; i < len; i++) {
            if (grid[x][y + i] - '0' != car && grid[x][y + i]!= '.') {
                return false;
            }
        }
    }

    return true;
}

void removeCar(string grid[], int x, int y, int len, bool vertical) {
    for (int i = 0; i < len; i++) {
        if (vertical) {
            grid[x + i][y] = '.';
        } else {
            grid[x][y + i] = '.';
        }
    }
}

RushHour::RushHour(string g[]) {
    grid[0] = "########";
    grid[7] = "########";
    for (int i = 0; i < 6; i++) {
        grid[i + 1] = g[i];
    }
    totalSteps = 0;
}

bool RushHour::locateCar(int car, int &row, int &col) const {
    for (int x = 1; x < 7; x++) {
        for (int y = 1; y < 7; y++) {
            if (grid[x][y] - '0' == car) {
                row = x;
                col = y;
                return true;
            }
        }
    }
    return false;
}

int RushHour::moveCar(int car, int step) {
    int row, col, len;
    bool vertical;
    if (locateCar(car, row, col) == false || step == 0) {
        return 1;
    }
    if (grid[row + 1][col] - '0' == car) {
        vertical = true;
    } else {
        vertical = false;
    }
    len = findLen(grid, car, row, col, vertical);
    //cout << row << " " << col << " " << (grid[row + 1][col] - '0' == car) << " " << vertical << "\n";
    if (vertical) {
        if (checkSpace(grid, car, len, row + step, col, vertical)) {
            removeCar(grid, row, col, len, vertical);
            for (int i = 0; i < len ; i++) {
                grid[row + step + i][col] = (char)(car + 48);
            }
        } else {
            return 2;
        }
    }  else if (vertical == false) {
        if (checkSpace(grid, car, len, row, col + step, vertical)) {
            removeCar(grid, row, col, len, vertical);
            for (int i = 0; i < len ; i++) {
                grid[row][col + step + i] = (char)(car + 48);
            }
        } else {
            return 2;
        }
    } 
    totalSteps += abs(step);
    return 0;
}

bool RushHour::isSolved() const {
    if (grid[3][7] == '0') {
        return true;
    } else {
        return false;
    }
}

int RushHour::getTotalSteps() const {
    return totalSteps;
}

void RushHour::print() const {
    for (int i = 0; i < 8; i++) {
        cout << grid[i] << "\n";
    }
    cout << "Steps: " << totalSteps << "\n";
}