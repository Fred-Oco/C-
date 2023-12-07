#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <climits>
// You may add additional headers if needed

#include "ActionCard.h"
#include "Man.h"
#include "Bot.h"
#include "DrawPile.h"
#include "DiscardPile.h"

using namespace std;

int main()
{
	// Get the game start-up parameters 
	string input;
	unsigned int seed = 123;
	cout << "Enter seed (or hit Enter): ";
	getline(cin, input);
	if (!input.empty()) {
		seed = stoi(input);
	}
	cout << "Seed: " << seed << endl;
	srand(seed);

	bool debugMode = false;
	cout << "Play in debug mode (Y/N)? ";
	getline(cin, input);
	if (input == "Y" || input == "y" || input == "") {
		debugMode = true;
	}
	cout << "Debug mode: " << boolalpha << debugMode << endl;

	int turnsMax = 100;
	cout << "Max. turns to play: ";
	getline(cin, input);
	if (!input.empty()) {
		turnsMax = stoi(input);
	}
	cout << "Max. turns: " << turnsMax << endl;

	int M, B, P;
	while (true) {
		cout << "Enter # man and bot players: ";
		cin >> M >> B;
		P = M + B;
		if (P >= 2 && P <= 5)
			break;
		cout << "Require 2 to 5 players!" << endl;
	}
	cout << "#Men: " << M << "; #Bots: " << B << endl;

	// Create an array of pointers to Player objects
	Player** players = new Player * [P];
	for (int i = 0; i < P; i++) {
		if (i < M)
			players[i] = new Man;
		else
			players[i] = new Bot;
	}
	Player* player = players[0];  // current player

	// Define variables to track the game state
	DrawPile drawPile;
	DiscardPile discardPile;
	bool turnSkipped = false;
	int cardsToDraw = 0;
	int delta = 1;
	int turn = 0;

	GameState uno{ players, &drawPile, &discardPile,
		&turnSkipped, &cardsToDraw, &turn, &delta, P, debugMode
	};

	// Shuffle the deck and deal cards to each player
	if (debugMode) {
        cout << "Cards created:" << endl;
        drawPile.print();
    }
	drawPile.shuffle();
	for (int i = 0; i < P; i++) {
		players[i]->drawCard(&drawPile, H);
	}

	// Draw the first card onto discard pile
	vector<Card*> firstCard;
	drawPile.draw(firstCard, 1);
	discardPile.stack(firstCard.at(0)); 
	if (debugMode) {
		cout << "Draw pile after shuffling and dealing:" << endl;
		drawPile.print();
	}

	// Start the game loop
	string fill(8, ' ');
	string cur_col;
	int pick, pass_count;
	while(true) {
		// TODO:
		// Print the "turn header" which shows discard pile's top card, 
		// current color and current size of draw pile.
		cout << "=========================================================\n";
		cout << "Turn " << *(uno.turn) + 1 << ":\n";
		cout << "Discard Pile: " << uno.discardPile -> top() -> toString();
		cur_col = COLORS[(int)uno.discardPile -> top() -> getColor()];
		cout << "  " << "Current Color: " << fill.replace(fill.begin(), fill.begin() + cur_col.size(), cur_col);
		cout << "Draw Pile: " << uno.drawPile -> size() << endl;
		cout << "---------------------------------------------------------\n";
		// Print the name of the current player.
		// (Hint: you can use the turn integer to index the players array
		//  to get a pointer to the current player.)
		player = players[*(uno.turn) % P];
		cout << player -> getName() << ":\n";
		// If cardsToDraw > 0, current player draws the required # cards.
		// If turnSkipped is true, current player skips picking and playing 
		// a card in this turn.
		// Otherwise, call the pickCard() method to get the index of a 
		// selected card in hand.
		// Then call the playCard() method with the obtained index if it is 
		// not PASSED and not DRAWN.
		if (*uno.cardsToDraw > 0) {
			player -> drawCard(uno.drawPile, *uno.cardsToDraw);
			cout << "Turn skipped!\n";
			*(uno.cardsToDraw) = 0;
			*(uno.turnSkipped) = false;
		} else if (*uno.turnSkipped) {
			cout << "Turn skipped!\n";
			*(uno.cardsToDraw) = 0;
			*(uno.turnSkipped) = false;
		} else {
			pick = player -> pickCard(uno);
			if (pick != DRAWN && pick != PASSED) {
				player -> playCard(pick, uno);
			}
		}
		// Check game over condition. Exit the game loop if either:
		// (1) current player's hand has no cards.
		// (2) all players consecutively passed their turns 
	    //     (i.e., no one can play a card or draw).

		if (pick == PASSED) {
			pass_count += 1;
		} else {
			pass_count = 0;
		}
		if (player -> handSize() == 0 || pass_count == P || *(uno.turn) == turnsMax) {
			break;
		}
		// Reset cardsToDraw and turnSkipped for clean state for next turn.
		// Update the turn integer to let the next player become current.
		*(uno.turn) += *(uno.delta);
		
	}
	// TODO:
	// Print the game over message.
	// List all players' hands and the sum of points of all cards in hand.
	// Print the name of the winner. 
}