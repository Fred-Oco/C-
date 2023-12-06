#ifndef REVERSE_H
#define REVERSE_H

#include "ActionCard.h"

class Reverse : public virtual ActionCard {
public:
    Reverse(Color c);
    virtual void play(GameState& uno) override;
};

#endif // REVERSE_H