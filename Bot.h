#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED
#include "Board.h"
class Bot {

	protected:
    friend class Controller;
	virtual Block makeMove(bool isLastMoveHit, bool isBoatsDestroyed[])=0; //return the block in which the bomb has to be dropped

	virtual Boat* positionBoats(Boat boats[])=0; // return the boats after making changed to its positions in the board, if needed

};



#endif // BOT_H_INCLUDED
