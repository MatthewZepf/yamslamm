#include "Player.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <sstream>
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
	int numDigits = (int) log10((double)input) + 1;
	for (int i = 0; i < numDigits; i++) {
		b.rollDiceAt(input % 10);
		input = input / 10;
	}
}


bool Player::doMove(Board& b) {
	if (numMoves == 0) {
		cout << "you roll all dice to start" << endl;
		b.rollAllDice();
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
	//yamslam check
	if (b.getDiceatIndex(0).getDieValue() == b.getDiceatIndex(4).getDieValue()) {
		cout << "yamslam?!?!?" << endl;
		return 100;
	}
	//large straight check
	else if ((b.getDiceatIndex(0).getDieValue() == 1 || (b.getDiceatIndex(0).getDieValue() == 2))) {
		if ((b.getDiceatIndex(0).getDieValue() == 1) && (b.getDiceatIndex(1).getDieValue() == 2) && (b.getDiceatIndex(2).getDieValue() == 3) && (b.getDiceatIndex(3).getDieValue() == 4) && (b.getDiceatIndex(4).getDieValue() == 5)) {
			cout << "Large straight" << endl;
			return 0;
		}
		else if ((b.getDiceatIndex(0).getDieValue() == 2) && (b.getDiceatIndex(1).getDieValue() == 3) && (b.getDiceatIndex(2).getDieValue() == 4) && (b.getDiceatIndex(3).getDieValue() == 5) && (b.getDiceatIndex(4).getDieValue() == 6)) {
			cout << "Large straight" << endl;
			return 0;
		}
	}
	// 4 of a kind
	else if ((b.getDiceatIndex(0).getDieValue() == b.getDiceatIndex(3).getDieValue()) || (b.getDiceatIndex(1).getDieValue() == b.getDiceatIndex(4).getDieValue())) {
		cout << "4 of a kind" << endl;
		return 1;
	} else if ((b.getDiceatIndex(0).getDieValue() == b.getDiceatIndex(2).getDieValue()) && (b.getDiceatIndex(3).getDieValue() == b.getDiceatIndex(4).getDieValue())) {
		return 2;
		cout << "full house";
	} else if ((b.getDiceatIndex(0).getDieValue() == b.getDiceatIndex(1).getDieValue()) && (b.getDiceatIndex(2).getDieValue() == b.getDiceatIndex(4).getDieValue())) {
		return 2;
		cout << "full house";
	}
	else if (b.getDiceatIndex(0).isRed() == b.getDiceatIndex(1).isRed() == b.getDiceatIndex(2).isRed() == b.getDiceatIndex(3).isRed() == b.getDiceatIndex(3).isRed()) {
		return 3;
		cout << "flush";
	} 
	return 10;
}