#include <iostream>
#include "ActionCard.h"

using namespace std;

ActionCard::ActionCard(Color c, Action a) : Card(c, Value::A), action(a) {
}

Action ActionCard::getAction() const {
    return action;
}

void ActionCard::setAction(Action a) {
    action = a;
}

bool ActionCard::match(Card* top) {
    ActionCard *aPtr;
    if (Card::getColor() == top->Card::getColor()) {
        return true;
    }
    aPtr = dynamic_cast<ActionCard *>(top);
    if (aPtr != NULL && aPtr->ActionCard::getAction() == ActionCard::getAction()) {
        return true;
    }
    return false;
}

string ActionCard::toString() {
     return string() + "[" + COLORS[int(Card::getColor())][0] + ACTIONS[int(ActionCard::getAction())][0] + "]";
}