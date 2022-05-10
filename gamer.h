#ifndef _GAMER_H_
#define _GAMER_H_
#include "Boardr.h"
#include <vector>
//basically just a functor
class Gamer {
	private:
		
		int numMoves = 0;
		vector<int> move;
	public:
		//gets user move, either taking a coin, or rolling the die
		//then applies the move
		void getUserMove();


		Board board;
};

#endif // ! _GAMER_H_

