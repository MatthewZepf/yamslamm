#ifndef _DICE_H_
#define _DICE_H_
class Dice {
	private:
		//holds dice value, must be between 1 and 6
		int value;
		
		//if red, is true, if black, is false
		bool colorRed;
	public:
		//creates a die with the given int as the value
		Dice(int number);

		//defualt constructor, sets value to -1
		Dice();

		//randomizes the value to be a int between 1 and 6
		void rollDie();

		//sets the die value to the given int
		void setDieValue(int val);

		//returns the die value
		int getDieValue();
		//returns 1 if red, 0 if not
		int isRed();

		bool operator<(const Dice& rhs) {
			return (this->value < rhs.value);
		}

};
#endif
