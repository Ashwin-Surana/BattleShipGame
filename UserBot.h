#ifndef USERBOT_H_INCLUDED
#define USERBOT_H_INCLUDED
#include <cstdlib>
#include <ctime>
using namespace std;
#include "Bot.h"

class UserBot: public Bot{
    friend class Controller;
	Block makeMove(bool isLastMoveHit, bool isBoatsDestroyed[]){
		int x = rand()%GameConfig::ROWS;
		int y = rand()%GameConfig::COLUMNS;
		return Block(x,y);
	}

	Boat* positionBoats(Boat boats[]) {
		for(int i = 0; i<GameConfig::NBOATS;i++){
			//set boat blocks
		}

		return boats;
	}

};



#endif // USERBOT_H_INCLUDED
