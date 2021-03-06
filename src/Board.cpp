#include "Board.h"

/* the below function sets all the blocks of each boat to NOT_BLASTED which indicates
* that the block is not targeted by the opponent yet
*/
void Board::placeBoats(Boat boats[]) {
    if(boatsPlaced == false){
        for(int i=0; i< GameConfig::NBOATS; i++){
            boatsDestroyed[i] = false;
            int startX = boats[i].startBlock.getX();
            int startY = boats[i].startBlock.getY();
            int endX = boats[i].endBlock.getX();
            int endY = boats[i].endBlock.getY();
            int boatLife = 0;
            if(startX == endX){
                for(int y = startY; y <= endY; y++){
                    blocks[startX][y].setStatus(GameConfig::NOT_BLASTED);
                    boatLife++;
                }
            }
            else if(startY == endY){
                for(int x = startX; x <= endX; x++){
                    blocks[x][startY].setStatus(GameConfig::NOT_BLASTED);
                    boatLife++;
                }
            }
            this->boats[i] = boats[i];
            this->boats[i].setBoatLife(boatLife);
        }
        boatsPlaced = true;
    }
}

bool Board::isAllBoatsBlasted() {
    bool boatsBlasted = true;

    for(int i = 0; i < GameConfig::NBOATS; i++){
        if(!boats[i].isDestoyed()){
            boatsBlasted = false;
            break;
        }
    }
    return boatsBlasted;
}

/*
* The below function returns true if the bomb has been dropped on a block which has a boat
*/
bool Board::dropBombOnBlock(Block block) {
    if(blocks[block.getX()][block.getY()].getStatus() == GameConfig::NOT_BLASTED){
        blocks[block.getX()][block.getY()].setStatus(GameConfig::BLASTED);
        for(int i = 0; i < GameConfig::NBOATS; i++){
            if(boats[i].isBoatAttacked(blocks[block.getX()][block.getY()])){
                //system("pause");
                //cout << boats[i].type << " Boat attacked" << endl;
                boats[i].decrementBoatLife();
                //cout << boats[i].boatLife << " Boat life" << endl;
                lastMoveHit = true;
                if(boats[i].isDestoyed()){
                    //cout << boats[i].type << " Boat destroyed" << endl;
                    boatsDestroyed[i] = true;
                }
                return true;
            }
        }
    }
    lastMoveHit = false;
    return false;
}

bool* Board::getAllBoatsStatus() {
    return boatsDestroyed;
}

bool Board::isLastMoveHit() {
    return lastMoveHit;
}
