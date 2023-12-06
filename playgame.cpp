#include <iostream>
#include <string>
#include "RushHour.h"

using namespace std;
int main() {
    string input[6];
    int car, step, status = -1; 
    cout << "Enter initial grid: ";
    for (int i = 0; i < 6; i++) {
        cin >> input[i];
    }
    RushHour Game(input);
    Game.print();
    while (Game.isSolved() == false && Game.getTotalSteps() < 100) {
        while(status != 0) {
            cout << "Move a car: ";
            cin >> car >> step;
            status = Game.moveCar(car, step);
            if (status == 1) {
                cout << "Invalid car or step! Try again." << "\n";
            } else if (status == 2) {
                cout << "Hit! Try again." << "\n";
            }
        }
        Game.print();
        status = -1;
    }
    if (Game.isSolved()) {
        cout << "Congrats! You finished in " << Game.getTotalSteps() << " steps.";
    } else {
        cout << "Oops! You could not solve in 100 steps";
    }
    
    return 0;
}