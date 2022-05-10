#include <iostream>
#include "Dice.h"
#include <random>

using namespace std;

Dice::Dice(int number) {
	//sets dice value to number
	value = number;
	if (value % 2 == 0) {
		colorRed = true;
	}
	else {
		colorRed = false;
	}
}

Dice::Dice() {
	value = -1;
	colorRed = false;
}

void Dice::rollDie() {
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist6(1, 6); // distribution in range [1, 6]

	value = dist6(rng);
	if (value % 2 == 0) {
		colorRed = true;
	}
	else {
		colorRed = false;
	}
}

void Dice::setDieValue(int number) {
	value = number;
}

int Dice::getDieValue() {
	return value;
}


int Dice::isRed() {
	if (colorRed)
		return 1;
	return 0;
}