#include <iostream>
#include "Boardr.h"
#include <algorithm>

void Board::defualtBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 0) {
				coins[i][j] = 50;
			}
			else if (i == 1) {
				coins[i][j] = 40;
			}
			else if (i == 2) {
				coins[i][j] = 30;
			}
			else if (i == 3) {
				coins[i][j] = 25;
			}
			else if (i == 4) {
				coins[i][j] = 20;
			}
			else if (i == 5) {
				coins[i][j] = 10;
			}
			else if (i == 6) {
				coins[i][j] = 5;
			}
			else if (i == 7) {
				coins[i][j] = 0;
			}
		}
	}
}

void Board::updateCoins(int number) {
	for (int i = 0; i < 4; i++) {
		if (coins[number][i] != 0) {
			coins[number][i] = 0;
			return;
		}
	}
	return;
}

void Board::updateDie(Dice d, int index) {
	die.at(index) = d;
	return;
}

void Board::printBoard() {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 4; j++) {
			cout << coins[i][j] << "  ";
			if (coins[i][j] < 10)
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	printDice();
}

void Board::rollAllDice() {
	for (int i = 0; i < 5; i++) {
		die[i].rollDie();
	}
}

void Board::rollDiceAt(int index) {
	die[index].rollDie();
}

void Board::sortDice() {
	sort(die.begin(), die.end());
}

void Board::printDice() {
	for (int i = 0; i < 5; i++) {
		cout << die[i].getDieValue() << "   ";
	}
	cout << endl;
	return;
}

int Board::highestCoinOnBoard() {
	int columnIndex = -1;
	int maxCoinValue = -1;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 4; j++) {
			if (coins[i][j] > maxCoinValue) {
				columnIndex = i;
				maxCoinValue = coins[i][j];
			}
		}
	}
	return columnIndex;
}

Dice Board::getDiceatIndex(int i) {
	return die[i];
}