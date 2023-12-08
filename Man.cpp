#include <iostream>
#include <iomanip>
#include <sstream>
// You may add additional headers if needed

#include "Man.h"

using namespace std;

Man::Man() : Player() {
    setName(getName() + " (Man)");
}

int Man::pickCard(GameState& uno) {
    // Show the hand of cards with selectable indexes
    // For each card in hand, print the card's string representation
    // with "[i]"" in front of it, where i is the index of the card
    // in the player's hand vector.
    // If the card cannot match the top of the discard pile, show 
    // "[x]" which means the card cannot be played.
    // Print at most 10 cards per line if there are many cards in hand.
    Card *Top = uno.discardPile -> top();
    bool ForcePass = true;
    for (int i = 0; i < Player::hand.size(); i++) {
        if (i == 10) {
            cout << endl;
        }
        cout << " [";
        if (Player::hand[i] -> match(Top) == true){
            cout << i;
            ForcePass = false;
        } else {
            cout << "x";
        }
        cout << "]";
        cout << Player::hand[i] -> toString() << " ";
    }

    // Show the [D]raw option if draw pile still has cards.
    if (uno.drawPile -> size() > 0) {
        if (Player::hand.size() == 10) {
            cout << "\n";
        }
        cout << " [D]raw\n";
        ForcePass = false;
    }

    // You may make an early return with PASSED if no matched cards in hand 
    // and draw pile is empty.
    if (ForcePass) {
        return PASSED;
    }

    // Get user input for the option (selected card index or 'D' for draw).
    // Keep prompting until the option is valid.
    // If the input is 'D' (case-insensitive), draw 1 card from draw pile 
    // into this player's hand vector. The drawn card is added to the back
    // of the vector. 
    // If the drawn card is playable, return its index. Otherwise, return 
    // the constant DRAWN to mean a card has been drawn but not playable.
    // The caller seeing DRAWN returned should skip playing any card.
    // If the input is an integer that can index a playable card in hand, 
    // return the integer.
    //
    // Print error message "Invalid option!" for invalid index or incorrect 
    // input.
    //
    // Hint: read the user input as a string first. You can convert it to
    // integer later using an input string stream or the stoi() function.
    // The string stream method is preferred as it can detect non-integer input.
    string choice = "";
    stringstream choice_str;
    int choice_int;
    while (true) {
        cout << "Enter option: ";
        cin >> choice;
        choice_str.clear();
        choice_str << choice;
        if (choice == "D" && uno.drawPile -> size() > 0) {
            uno.drawPile -> draw(Player::hand);
            cout << Player::getName() << " drawn 1 card(s).\n";
            cout << "Drawn " << Player::hand[Player::hand.size() - 1] -> toString() << endl;
            if (Player::hand[Player::hand.size() - 1] -> match(Top)){
                return (Player::hand.size() - 1);
            } else {
                return DRAWN;
            }
        }
        choice_str >> choice_int;
        if (choice_int < 0 || choice_int > Player::hand.size() - 1 || Player::hand[choice_int] -> match(Top) == false) {
            cout << "Invalid option!\n";
            continue;
        }
        if (choice_int == 0 && choice != "0") {
            cout << "Invalid option!\n";
            continue;
        }
        return choice_int;
    }
    return -1;
}
