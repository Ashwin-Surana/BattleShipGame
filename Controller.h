#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED
#include <vector>
#include <fstream>
using namespace std;
#include "ComputerBot.h"
class Controller {

	Bot *userBot;
	Bot *computerBot;
	int currentTurn;
public:
    Controller() {
        userBot = new UserBot();
        computerBot = new ComputerBot();
        srand(time(NULL));
        ofstream ofs;
        ofs.open("Battleship.json", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }

	int getBoatSize(Boat boat) {

		switch(boat.type){
		case GameConfig::AIRCRAFT:
			return GameConfig::AIRCRAFT_SIZE;

		case GameConfig::BATTLESHIP:
			return GameConfig::BATTLESHIP_SIZE;

		case GameConfig::DESTROYER:
			return GameConfig::DESTROYER_SIZE;

		case GameConfig::PATROL:
			return GameConfig::PATROL_SIZE;

		case GameConfig::SUBMARINE:
			return GameConfig::SUBMARINE_SIZE;
		}
		return -1;
	}

	bool validateBoatPosition(Boat boats[]) {
		if(GameConfig::NBOATS != GameConfig::NBOATS) {
			return false;
		}

		// Validating each boat is placed only once...

		vector<GameConfig::BoatType> allBoatTypes;

		for(int i=0;i<GameConfig::NBOATS;i++){
			for(unsigned int j = 0; j < allBoatTypes.size(); j++)
                if(allBoatTypes[j] == boats[i].type){
                    return false;
			}
			allBoatTypes.push_back(boats[i].type);
		}

		for(int i=0;i<GameConfig::NBOATS;i++){
			// Validating horizontal constraint or vertical constraint...
			//cout << boats[i].getStartBlock().getX() << " " << boats[i].getEndBlock().getX() << " " << boats[i].getStartBlock().getY() << " " << boats[i].getEndBlock().getY() << endl;
			if(!((boats[i].getStartBlock().getX() == boats[i].getEndBlock().getX() ) || (boats[i].getStartBlock().getY() == boats[i].getEndBlock().getY()))){
				//cout << "Diagonal Constraint" << endl;
				return false;

			}

			// Validating size...
			if(!(getBoatSize(boats[i]) == boats[i].getBoatSizeBlock())){

				//cout << "Size " << boats[i].getBoatSizeBlock() <<  getBoatSize(boats[i]) << endl;
				return false;
			}
		}

		// overlaping boat...

		for(int row = 0 ; row<GameConfig::ROWS;row++){
			for(int column =0; column<GameConfig::COLUMNS;column++){
				bool flag=false;
				for(int iBoat =0; iBoat < GameConfig::NBOATS ;iBoat++){
					if(boats[iBoat].isBlockInBoat(Block(row,column))){
						if(flag== false){
							flag = true;
						}
						else{
							//cout << "Overlapping" << endl;
							return false;
						}
					}
				}
			}
		}




		return true;
	}


	void start(){

		Board *userBoard = new Board();
		Board *computerBoard = new Board();

		Boat userBoats[GameConfig::NBOATS];
		initialBoatArrangement(userBoats);
		userBot->positionBoats(userBoats);
        fstream f("Battleship.json",ios::in | ios::out | ios::app);
        f << endl << "{" << endl << "\"Details\" :" << endl << "{";

		if(validateBoatPosition(userBoats)){
			userBoard->placeBoats(userBoats);
        f << "\"UserBoats\" : " << endl << "[";
		for(int i=0;i<GameConfig::NBOATS;i++){
            f << endl << "{";
			f << "\"startRow\" : \"" << userBoats[i].startBlock.getX() << "\"," << endl;
			f << "\"startColumn\" : \"" << userBoats[i].startBlock.getY() << "\"," << endl;
			f << "\"endRow\" : \"" << userBoats[i].endBlock.getX() << "\"," << endl;
			f << "\"endColumn\" : \"" << userBoats[i].endBlock.getY() << "\"," << endl;
			f << "\"Boat\" : \"" << i << "\""<< endl;
			if(i != GameConfig::NBOATS - 1)
                f << "},";
            else
                f << "}";
		}
		}
		else {
			//cout << "not valid positioning" << endl;
			return;
		}
		f << "]," << endl;


		Boat computerBoats[GameConfig::NBOATS];
		initialBoatArrangement(computerBoats);
		computerBot->positionBoats(computerBoats);
		if(validateBoatPosition(computerBoats)){
		computerBoard->placeBoats(computerBoats);
		f << "\"ComputerBoats\" : " << endl << "[";
		for(int i=0;i<GameConfig::NBOATS;i++){
            f << endl << "{";
			f << "\"startRow\" : \"" << computerBoats[i].startBlock.getX() << "\"," << endl;
			f << "\"startColumn\" : \"" << computerBoats[i].startBlock.getY() << "\"," << endl;
			f << "\"endRow\" : \"" << computerBoats[i].endBlock.getX() << "\"," << endl;
			f << "\"endColumn\" : \"" << computerBoats[i].endBlock.getY() << "\"," << endl;
			f << "\"Boat\" : \"" << i << "\""<< endl;
			if(i != GameConfig::NBOATS - 1)
                f << "},";
            else
                f << "}";
		}
		}
		else {
			//cout << "Not valid positioning" << endl;
			return;
		}
		f << endl << "]" << endl << "}," << endl;
		srand(time(NULL));
		int x = rand()%2;
		currentTurn = x+1;

		play(userBoard,computerBoard);

		int winner = declareWinner(userBoard, computerBoard);

		if(winner == GameConfig::USERBOT)
			cout << "Winner is User Bot" << endl;

		else if(winner == GameConfig::COMPUTERBOT)
			cout << "Winner is Computer Bot" << endl;

	}

	/*
	 * The below function provides the default positioning of the boats in a board
	 * To be changed later
	 */
	void initialBoatArrangement(Boat boats[]) {
		boats[0].setBoat(GameConfig::AIRCRAFT,Block(5,2),Block(5,5));
		boats[1].setBoat(GameConfig::BATTLESHIP,Block(0,0),Block(4,0));
		boats[2].setBoat(GameConfig::DESTROYER,Block(1,9),Block(3,9));
		boats[3].setBoat(GameConfig::SUBMARINE,Block(7,2),Block(9,2));
		boats[4].setBoat(GameConfig::PATROL,Block(7,6),Block(8,6));
	}

	int declareWinner(Board *userBoard, Board *computerBoard){
		if(userBoard->isAllBoatsBlasted())
			return GameConfig::COMPUTERBOT;
		else
			return GameConfig::USERBOT;
	}

	/*
	 * The below function keeps the game continuing until any one of the board has lost its ships
	 */
	void play(Board *userBoard, Board *computerBoard) {
        fstream f("Battleship.json",ios::in | ios::out | ios::app);
        f << endl << "\"moves\" : [";
        f.close();
		while(true){
			makeMove(userBoard, computerBoard);

			if(!userBoard->isAllBoatsBlasted() && !computerBoard->isAllBoatsBlasted()){
                fstream f("Battleship.json",ios::in | ios::out | ios::app);
                f << ",";
                f.close();
			}
            else{
                break;
            }

		}
		fstream f1("Battleship.json",ios::in | ios::out | ios::app);
		f1 << endl << "]" << endl << "}";
		f1.close();
	}

	void makeMove(Board *userBoard, Board *computerBoard) {

	//	JSONObject move = new JSONObject();
        fstream f("Battleship.json",ios::in | ios::out | ios::app);
		if(currentTurn == GameConfig::USERBOT){

			Block block = userBot->makeMove(computerBoard->isLastMoveHit(), computerBoard->getAllBoatsStatus());

			bool hit = computerBoard->dropBombOnBlock(block);

			if(!hit){ // if a boat has been hit, the bot gets one more turn, else turn goes to the opponent
				currentTurn = GameConfig::COMPUTERBOT;
			}
			else{
                //cout << "userboard" << endl;
			}
			f << endl << "{";
			f << "\"player\" : \"UserBot\"," << endl;
			f << "\"row\" : \"" << block.getX() << "\"," << endl;
			f << "\"column\" : \"" << block.getY() << "\"," << endl;
			f << "\"hit\" : \"" << hit << "\"," << endl;
			f << "}";
		}
		else if(currentTurn == GameConfig::COMPUTERBOT){

			Block block = computerBot->makeMove(userBoard->isLastMoveHit(), userBoard->getAllBoatsStatus());
			bool hit = userBoard->dropBombOnBlock(block);

			if(!hit){
				currentTurn = GameConfig::USERBOT;
			}
			else{
                //cout << "computerboard" << endl;
			}
			f << endl << "{";
			f << "\"player\" : \"ComputerBot\"," << endl;
			f << "\"row\" : \"" << block.getX() << "\"," << endl;
			f << "\"column\" : \"" << block.getY() << "\"," << endl;
			f << "\"hit\" : \"" << hit << "\"," << endl;
			f << "}";
		}
		f.close();
	}



};



#endif // CONTROLLER_H_INCLUDED
