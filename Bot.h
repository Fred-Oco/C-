#ifndef BOT_H
#define BOT_H

#include "Player.h"

class Bot : public Player
{
public:
    Bot();
    virtual int pickCard(GameState& uno) override;
};


#endif // BOT_H