#include "Player.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <set>
using namespace std;

void Player::takeCoin(Board& b, int location) {
	if ((b.coins[location][0] == 0)) {
		cout << "no coin was taken" << endl;
	}
	else {
		if (b.coins[location][3] != 0) {
			numCoins += b.coins[location][3];
			b.coins[location][3] = 0;
		}
		else if (b.coins[location][2] != 0) {
			numCoins += b.coins[location][3];
			b.coins[location][3] = 0;
		}
		else if (b.coins[location][2] != 0) {
			numCoins += b.coins[location][3];
			b.coins[location][2] = 0;
		}
		else if (b.coins[location][1] != 0) {
			numCoins += b.coins[location][3];
			b.coins[location][1] = 0;
		}
		else if (b.coins[location][0] != 0) {
			numCoins += b.coins[location][3];
			b.coins[location][0] = 0;
		}
	}
}
void Player::rollDie(Board& b, int input) {
	//b.printDice();
	//cout << "please select dice you would like to roll by entering them in like 013" << endl;
	//int input;
	//cin >> input;
	int numDigits = (int)log10((double)input) + 1;
	for (int i = 0; i < numDigits; i++) {
		b.rollDiceAt(input % 10);
		input = input / 10;
	}
}


bool Player::doMove(Board& b) {
	if (numMoves == 0) {
		cout << "you roll all dice to start" << endl;
		b.rollAllDice();
		b.printDice();
		numMoves++;
		return true;
	}
	else if (numMoves == 1 || numMoves == 2) {
		cout << "the current highest coin you may take is " << endl;
		stringstream ss;
		ss << b.coins[bestCoinWithDice(b)][0];
		string str = ss.str();
		cout << str << endl;
		cout << "this is the board" << endl;
		b.printBoard();
		cout << "if you would like to take the coin, please enter -1, else please enter the numbers of the die to be rolled" << endl;
		int input;
		cin >> input;
		if (input == -1) {
			numMoves = 0;
			takeCoin(b, bestCoinWithDice(b));
			return false;
		}
		else {
			rollDie(b, input);
			numMoves++;
			return true;
		}
	}
	else {
		numMoves = 0;
		takeCoin(b, bestCoinWithDice(b));
		return false;
	}
}

int Player::bestCoinWithDice(Board& b) {
	b.sortDice();
	set <int> die_set;
	for (int i = 0; i < 5; i++) {
		die_set.insert(b.getDiceatIndex(i).getDieValue());
	}
	auto counter = die_set.begin();
	int first = *counter + 1;
	switch (die_set.size()) {
	case 1:
		//cout << "Yamslam" << endl;
		return 0;
		break;
	case 2:
		if ((b.getDiceatIndex(0).getDieValue() == b.getDiceatIndex(3).getDieValue()) || (b.getDiceatIndex(1).getDieValue() == b.getDiceatIndex(4).getDieValue())) {
			//cout << "4 of a kind" << endl;
			return 1;
		}
		else {
			//cout << "full house" << endl;
			return 2;
		}
		break;
	case 3:
		// flush statement no work :(
		if ((((b.getDiceatIndex(0).isRed() == b.getDiceatIndex(1).isRed()) && (b.getDiceatIndex(1).isRed() == b.getDiceatIndex(2).isRed())) && (b.getDiceatIndex(2).isRed() == b.getDiceatIndex(3).isRed())) && (b.getDiceatIndex(3).isRed() == b.getDiceatIndex(4).isRed()))  {
			//cout << "flush" << endl;
			return 3;
		} else if ((b.getDiceatIndex(0).getDieValue() == b.getDiceatIndex(2).getDieValue()) || (b.getDiceatIndex(1).getDieValue() == b.getDiceatIndex(3).getDieValue()) || (b.getDiceatIndex(2).getDieValue() == b.getDiceatIndex(4).getDieValue())) {
			//cout << "3 of a kind" << endl;
			return 5;
		}
		else {
			//cout << "two pair" << endl;
			return 6;
		}
		break;
	case 4:
		for (auto itr = die_set.begin(); itr != die_set.end(); ++itr) {
			if (*itr + 1 != first) {
				return 7;
			}
			first++;
		}
		//cout << "Small straight" << endl;
		return 4;
	case 5:
		if ((b.getDiceatIndex(0).getDieValue() == 1) && (b.getDiceatIndex(1).getDieValue() == 2) && (b.getDiceatIndex(2).getDieValue() == 3) && (b.getDiceatIndex(3).getDieValue() == 4) && (b.getDiceatIndex(4).getDieValue() == 5)) {
			//cout << "Large straight" << endl;
			return 0;
		}
		else if ((b.getDiceatIndex(0).getDieValue() == 2) && (b.getDiceatIndex(1).getDieValue() == 3) && (b.getDiceatIndex(2).getDieValue() == 4) && (b.getDiceatIndex(3).getDieValue() == 5) && (b.getDiceatIndex(4).getDieValue() == 6)) {
			//cout << "Large straight" << endl;
			return 0;
		}
		//small straight
		else if ((b.getDiceatIndex(0).getDieValue() == 1) && (b.getDiceatIndex(1).getDieValue() == 2) && (b.getDiceatIndex(2).getDieValue() == 3) && (b.getDiceatIndex(3).getDieValue() == 4)) {
			//cout << "Small straight" << endl;
			return 4;
		}
		else if ((b.getDiceatIndex(0).getDieValue() == 2) && (b.getDiceatIndex(1).getDieValue() == 3) && (b.getDiceatIndex(2).getDieValue() == 4) && (b.getDiceatIndex(3).getDieValue() == 5)) {
			//cout << "Small straight" << endl;
			return 4;
		}
		else if ((b.getDiceatIndex(1).getDieValue() == 3) && (b.getDiceatIndex(2).getDieValue() == 4) && (b.getDiceatIndex(3).getDieValue() == 5) && (b.getDiceatIndex(4).getDieValue() == 6)) {
			//cout << "Small straight" << endl;
			return 4;
		}
		else {
			return 7;
		}
	defualt:
		cout << "error, dice set size not valid" << endl;
	}
	return 7;
}

/*
* std::map
* switch statement for map size 
* case 1: yamslam
* case 2: 4 of kind | full house
* case 3: 3 of kind | 2 pair
* case 4: small striaght | nothing
* case 5: large straight | nothing
* dont forget flush
*/ 
