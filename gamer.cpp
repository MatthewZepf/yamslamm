#include "gamer.h"
#include <iostream>
#include <algorithm>

using namespace std;

void Gamer::getUserMove() {
	//have something here for the option to take highest coin
	
	cout << "This is the current state of your dice" << endl;
	board.printDice();
	int input = -2;
	int counter = 0;
	cout << "Enter a dice you would like to roll, if you dont want to roll a die enter -1" << endl;
	cin >> input;
	while (input != -1 && counter < 6) {
		move.push_back(input);
		counter++;
		cout << "Enter a dice you would like to roll, if you dont want to roll a die enter -1" << endl;
		cin >> input;
	}
	for (vector<int>::iterator it = move.begin(); it < move.end(); it++) {
		board.getDiceatIndex(*it).rollDie();
	}
	numMoves++;
}




