#include <iostream>
#include "Player.h"

using namespace std;

int Player::count = 0; 

Player::Player() {
    count++;
    name = "Player " + to_string(count);
}

string Player::getName() const {
    return name;
}

void Player::setName(string name_) {
    name = name_;
}

int Player::drawCard(DrawPile* drawPile, int n) {
    int d = drawPile->draw(hand, n);
    if (d == 0) {
        cout << "No more cards on draw pile!" << endl;
    }
    else {
        cout << name << " drawn " << d << " card(s)." << endl;
    }
    return d;
}

void Player::printHand(bool flipped) {
    // Print all cards in the player's hand in one line.
    // If flipped is true, print the front of each card, e.g. [R1], [GS], [WD]
    // Otherwise, print the back of each card, i.e., "[Uno]".
    if (flipped) {
        for (int i = 0; i < hand.size(); i++) {
            cout << " " << hand[i] -> toString() << " ";
    }
    } else {
        for (int i = 0; i < hand.size(); i++) { 
            cout << " [Uno] ";
        }
    }

    cout << endl;
}

int Player::handSize() const {
    return int(hand.size());
}

int Player::handPoints() const {
    // Compute and return the sum of values of all cards in hand 
    int sum = 0;
    for (int i = 0; i < hand.size(); i++) {
        sum += int(hand[i] -> getValue());
    }
    return sum;
}

void Player::playCard(int idx, GameState& uno) {
    // Locate the card at index idx and play it, 
    // i.e. call its play() function
    Card * card;
    card = hand[idx];
    card -> play(uno);
    // Move the card from hand to discard pile
    uno.discardPile->stack(card);
    hand.erase(hand.begin() + idx);
}

Color Player::mostFrequentColor() {
    // Return the color that appears most frequently in the hand.
    // Exclude wild (draw 4) cards in this search.
    // If more than one color are equally most frequent, select the color
    // to return in this order: Red, Yellow, Green, Blue.
    int Color_appear[4] = {0, 0, 0, 0}; 
    int Card_c, max = 0;
    for (int i = 0; i < hand.size(); i++) {
        Card_c = int(hand[i]->getColor());
        if (Card_c <= 4) {
            Color_appear[Card_c - 1] += 1;
            if (Color_appear[Card_c - 1] > max) {
                max = Color_appear[Card_c - 1];
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        if (Color_appear[i] == max) {
            return Color(i + 1);
        }
    }

}

