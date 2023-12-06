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
    cout << "[";
    switch(Card::getColor()){
        case(Color::Red):
            cout << "R";
            break;
        case(Color::Yellow):
            cout << "Y";
            break;
        case(Color::Green):
            cout << "G";
            break;
        case(Color::Blue):
            cout << "B";
            break;
        case(Color::Wild):
            cout << "W";
            break;
    }
    switch(ActionCard::getAction()){
        case(Action::Skip):
            cout << "S";
            break;
        case(Action::Reverse):
            cout << "R";
            break;
        case(Action::Draw2):
            cout << "D";
            break;
        case(Action::ChgColor):
            cout << "C";
            break;
        case(Action::Draw4):
            cout << "D";
            break;
    }
    cout << "]";
     return string() + "[" + COLORS[int(Card::getColor())][0] + ACTIONS[int(ActionCard::getAction())][0] + "]";
}