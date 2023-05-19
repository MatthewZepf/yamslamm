
#define _PLAYER_H_
#include <string>
#include "Boardr.h"

class Player {
private: 
	string name;

public:
	int numMoves = 0;
	int numCoins = 0;
	Player(string name_in) 
		: name(name_in)
	{}
	// given the players dice array and the board
	// returns location of coin in die array
	int bestCoinWithDice(Board& b);

	//takes coin in die array, adds it to player coin count
	void takeCoin(Board& b, int location);

	// gives user input for what die to roll then rolls them
	void rollDie(Board& b, int input);

	// utalizes roll die and bestCoinWithDice 
	// increments numMoves
	bool doMove(Board& b);

};


