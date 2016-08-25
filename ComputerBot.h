#ifndef COMPUTERBOT_H_INCLUDED
#define COMPUTERBOT_H_INCLUDED
#include <cstdlib>
#include <ctime>
using namespace std;
#include "Bot.h"

class ComputerBot: public Bot{
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



#endif // COMPUTERBOT_H_INCLUDED
