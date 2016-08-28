#ifndef USERBOT_H_INCLUDED
#define USERBOT_H_INCLUDED
#include <cstdlib>
#include <ctime>
using namespace std;
#include "Bot.h"

class UserBot: public Bot{
    public:
    UserBot(){}
    UserBot(UserBot const &uc){}
	Block makeMove(bool isLastMoveHit, bool isBoatsDestroyed[]);
	Boat* positionBoats(Boat boats[]);
};



#endif // USERBOT_H_INCLUDED
