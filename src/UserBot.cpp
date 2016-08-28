#include "UserBot.h"
Block UserBot::makeMove(bool isLastMoveHit, bool isBoatsDestroyed[]){
    int x = rand()%GameConfig::ROWS;
    int y = rand()%GameConfig::COLUMNS;
    return Block(x,y);
}

Boat* UserBot::positionBoats(Boat boats[]) {
    for(int i = 0; i<GameConfig::NBOATS;i++){
        //set boat blocks
    }
    return boats;
}
