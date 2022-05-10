#ifndef _BOARD_H_
#define _BOARD_H_
#include "Dice.h"

using namespace std;

class Board {
	private:
		//Array of all the dice
		Dice die[5];


	public:
		
		//sets board to defualt values (all coins are reset to full) 
		void defualtBoard();

		//finds coin with given int in coins array, and sets it to 0
		//might want to return bool?
		void updateCoins(int number);

		//updates die array
		void updateDie(Dice d, int index);

		//7 different coins and 4 of each of that coin
		//might want to make a separate class for them
		int coins[7][4];

		//prints coins array
		void printBoard();

		//rolls all the die
		void rollAllDice();
		
		//rolls all the die
		void rollDiceAt(int index);

		//prints all the dice
		void printDice();

		//sorts die array 
		void sortDice();

		//returns highest coin possible given the die array, 
		//if no coin applicable returns -1
		int highestCoinOnBoard();

		//returns dice at index i
		Dice getDiceatIndex(int i);
};
#endif // !_Board_H_

