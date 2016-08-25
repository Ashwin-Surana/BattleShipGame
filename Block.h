#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "GameConfig.h"
class Block {
private:
    int x;
	int y;
	GameConfig::BlockStatus status;
    friend class Boat;
    friend class Board;
    friend class Controller;
	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	GameConfig::BlockStatus getStatus() {
		return status;
	}

	void setStatus(GameConfig::BlockStatus newStatus) {
		this->status = newStatus;
	}

	bool isBlasted() {
		if(status == GameConfig::BLASTED)
			return true;

		return false;
	}
public:
    void setBlock(int x, int y){
        this->x = x;
		this->y = y;
    }
    Block(int x, int y){
        this->x = x;
		this->y = y;
		this->status = GameConfig::UNTOUCHED; // initially no block is touched
    }
	Block(Block const &B) {
		this->x = B.x;
		this->y = B.y;
		this->status = B.status;
	}
	Block(){
        this->status = GameConfig::UNTOUCHED;
	}
};


#endif // BLOCK_H_INCLUDED
