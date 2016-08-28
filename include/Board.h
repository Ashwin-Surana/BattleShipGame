#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include<vector>
using namespace std;
#include "Boat.h"
class Board {
private:
    Block blocks[GameConfig::ROWS][GameConfig::COLUMNS];
    Boat boats[GameConfig::NBOATS];
	bool boatsPlaced;
	bool boatsDestroyed[GameConfig::NBOATS];
	bool lastMoveHit;
public:
    Board();
	void initializeBlocks();
	/* the below function sets all the blocks of each boat to NOT_BLASTED which indicates
	 * that the block is not targeted by the opponent yet
	 */
	void placeBoats(Boat boats[]);
	bool isAllBoatsBlasted();
	/*
	 * The below function returns true if the bomb has been dropped on a block which has a boat
	 */
	bool dropBombOnBlock(Block block);
	bool* getAllBoatsStatus();
	bool isLastMoveHit();
};


#endif // BOARD_H_INCLUDED
