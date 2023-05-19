// Yamslam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Dice.cpp"
#include "Board.cpp"
#include "Player.cpp"
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
Dice d1(1);
Dice d2(2);
Dice d3(3);
Dice d4(4);
Dice d5(5);
Dice d6(6);
//calculates average value for a single roll
//i.e. 1/6 * value if die was 1 + if die was 2 + 3...6
double roll(Player &p, Board b, int index) {
    vector<Dice> original = b.die;
    int total = 0;
    b.updateDie(d1, index);
    total += b.coins[p.bestCoinWithDice(b)][0];
    b.die = original;
    b.updateDie(d2, index);
    total += b.coins[p.bestCoinWithDice(b)][0];
    b.die = original;
    b.updateDie(d3, index);
    total += b.coins[p.bestCoinWithDice(b)][0];
    b.die = original;
    b.updateDie(d4, index);
    total += b.coins[p.bestCoinWithDice(b)][0];
    b.die = original;
    b.updateDie(d5, index);
    total += b.coins[p.bestCoinWithDice(b)][0];
    b.die = original;
    b.updateDie(d6, index);
    total += b.coins[p.bestCoinWithDice(b)][0];
    //b.die = original;
    return (double)(1.0 / 6.0) * (total);
}

// returns a vector with the indices of the dice to roll and the expected value of rolling those dice given the current board state and one roll left
vector<double> OneRollLeft(Player &p, Board b) {
    double currentMaxValue = b.coins[p.bestCoinWithDice(b)][0];
    vector<double> indices;
    b.sortDice();
    double value = 0;
    for (int i = 0; i < 5; i++) {
        value = roll(p, b, i);
        if (value > currentMaxValue) {
            currentMaxValue = value;
            indices.clear();
            indices.push_back(i);
        }
    }
    value = 0;
    Board BoardCopy = b;
    // for each unique combination of two indices between 0 and 4, roll the dice at those indices and see if the expected value is higher than the current max value
    for (int i = 0; i < 5; ++i) {
        BoardCopy = b;
        for (int j = 1 + i; j < 5; ++j) {
            value = 0;
            for (int k = 1; k < 7; ++k) {
                Dice d(k);
                BoardCopy.updateDie(d, i);
                value += roll(p, BoardCopy, j);
            }
            if ((value / 6) > currentMaxValue) {
                currentMaxValue = value / 6;
                indices.clear();
                indices.push_back(i);
                indices.push_back(j);
            }  
        }
    }
    // for each combination of three indices between 0 and 4, roll the dice at those indices and see if the expected value is higher than the current max value
    for (int i = 0; i < 5; ++i) {
        for (int j = 1 + i; j < 5; ++j) {
            BoardCopy = b;
            for (int k = 1 + j; k < 5; ++k) {
                value = 0;
                for (int l = 1; l < 7; ++l) {
                    Dice d(l);
                    BoardCopy.updateDie(d, i);
                    for(int z = 1; z < 7; ++z) {
                        Dice d(z);
                        BoardCopy.updateDie(d, j);
                        value += roll(p, BoardCopy, k);
                        }
                    }
                    if ((value / 36) > currentMaxValue) {
                        currentMaxValue = value / 36;
                        indices.clear();
                        indices.push_back(i);
                        indices.push_back(j);
                        indices.push_back(k);
                    }
                }
            }
        }
    // for each combination of four indices between 0 and 4, roll the dice at those indices and see if the expected value is higher than the current max value
    /*for (int i = 0; i < 5; ++i) {
        for (int j = 1 + i; j < 5; ++j) {
            for (int k = 1 + j; k < 5; ++k) {
                BoardCopy = b;
                for (int l = 1 + k; l < 5; ++l) {
                    value = 0;
                    for (int m = 1; m < 7; ++m) {
                        Dice d(m);
                        BoardCopy.updateDie(d, i);
                        for(int z = 1; z < 7; ++z) {
                            Dice d(z);
                            BoardCopy.updateDie(d, j);
                            for(int y = 1; y < 7; ++y) {
                                Dice d(y);
                                BoardCopy.updateDie(d, k);
                                value += roll(p, BoardCopy, l);
                            }
                        }
                    }
                    if ((value / 216) > currentMaxValue) {
                            currentMaxValue = value / 216;
                            indices.clear();
                            indices.push_back(i);
                            indices.push_back(j);
                            indices.push_back(k);
                            indices.push_back(l);
                    }
                }
            }
        }
    }*/
    indices.push_back(currentMaxValue);
    return indices;
}
// returns a vector with the indices of the dice to roll and the expected value of rolling those dice given the current board state and two rolls left
vector<double> TwoRollsLeft(Player &p, Board &b) {
    double currentMaxValue = b.coins[p.bestCoinWithDice(b)][0];
    vector<double> indices;
    vector<double> temp;
    double value = 0;
    Board BoardCopy = b;
    b.sortDice();
    // from 0 to 4, update the die array at that index to be values 1-6, call OneRollLeft, add up the expected values, and divide by 6 to get the average expected value
    for (int i = 0; i < 5; i++) {
        value = 0;
        BoardCopy = b;
        for (int j = 1; j < 7; j++) {
            Dice d(j);
            BoardCopy.updateDie(d, i);
            temp = OneRollLeft(p, BoardCopy);
            value += temp[temp.size() - 1];
        }
        if ((value / 6) > currentMaxValue) {
            currentMaxValue = value / 6;
            indices.clear();
            indices.push_back(i);
        }
    }
    // for each unique combination of two indices between 0 and 4, update the die array at those indices to be values 1-6, call OneRollLeft, add up the expected values, and divide by 36 to get the average expected value
    for (int i = 0; i < 5; ++i) {
        for (int j = 1 + i; j < 5; ++j) {
            BoardCopy = b;
            value = 0;
            for (int k = 1; k < 7; ++k) {
                Dice d(k);
                BoardCopy.updateDie(d, i);
                for(int z = 1; z < 7; ++z) {
                    Dice d(z);
                    BoardCopy.updateDie(d, j);
                    temp = OneRollLeft(p, BoardCopy);
                    value += temp[temp.size() - 1];
                }
            }
            if ((value / 36) > currentMaxValue) {
                currentMaxValue = value / 36;
                indices.clear();
                indices.push_back(i);
                indices.push_back(j);
            }  
        }
    }
    // for each combination of three indices between 0 and 4, update the die array at those indices to be values 1-6, call OneRollLeft, add up the expected values, and divide by 216 to get the average expected value
    for (int i = 0; i < 5; ++i) {
        for (int j = 1 + i; j < 5; ++j) {
            for (int k = 1 + j; k < 5; ++k) {
                BoardCopy = b;
                value = 0;
                for (int l = 1; l < 7; ++l) {
                    Dice d(l);
                    BoardCopy.updateDie(d, i);
                    for(int z = 1; z < 7; ++z) {
                        Dice d(z);
                        BoardCopy.updateDie(d, j);
                        for(int y = 1; y < 7; ++y) {
                            Dice d(y);
                            BoardCopy.updateDie(d, k);
                            temp = OneRollLeft(p, BoardCopy);
                            value += temp[temp.size() - 1];
                        }
                    }
                }
                if ((value / 216) > currentMaxValue) {
                    currentMaxValue = value / 216;
                    indices.clear();
                    indices.push_back(i);
                    indices.push_back(j);
                    indices.push_back(k);
                }
            }
        }
    }
    // for each combination of four indices between 0 and 4, update the die array at those indices to be values 1-6, call OneRollLeft, add up the expected values, and divide by 1296 to get the average expected value
    for (int i = 0; i < 5; ++i) {
        for (int j = 1 + i; j < 5; ++j) {
            for (int k = 1 + j; k < 5; ++k) {
                for (int l = 1 + k; l < 5; ++l) {
                    BoardCopy = b;
                    value = 0;
                    for (int m = 1; m < 7; ++m) {
                        Dice d(m);
                        BoardCopy.updateDie(d, i);
                        for(int z = 1; z < 7; ++z) {
                            Dice d(z);
                            BoardCopy.updateDie(d, j);
                            for(int y = 1; y < 7; ++y) {
                                Dice d(y);
                                BoardCopy.updateDie(d, k);
                                for(int x = 1; x < 7; ++x) {
                                    Dice d(x);
                                    BoardCopy.updateDie(d, l);
                                    temp = OneRollLeft(p, BoardCopy);
                                    value += temp[temp.size() - 1];
                                }
                            }
                        }
                    }
                    if ((value / 1296) > currentMaxValue) {
                        currentMaxValue = value / 1296;
                        indices.clear();
                        indices.push_back(i);
                        indices.push_back(j);
                        indices.push_back(k);
                        indices.push_back(l);
                    }
                }
            }
        }
    }
    indices.push_back(currentMaxValue);
    return indices;
}

//goes through all possible dice combinations and returns a vector with the highest expected value and the indices of the dice to roll which get that expected value
vector<double> bestExpectedValue(Player &p, Board &b, int NumberofRollsLeft) {
    if (NumberofRollsLeft == 1) {
        return OneRollLeft(p, b);
    } else if (NumberofRollsLeft == 2) {
        return TwoRollsLeft(p, b);
    } else {
        return OneRollLeft(p, b);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    Board b;
    b.defualtBoard();
    string name = "Matthew";
    Player p1(name);
    b.updateDie(d2, 0);
    b.updateDie(d3, 1);
    b.updateDie(d4, 2);
    b.updateDie(d6, 3);
    b.updateDie(d4, 4);
    int rolls = 2;
    vector<double> result = bestExpectedValue(p1, b, rolls);
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << endl;
    }
    // create a REPL Loop while the input string is not "quit", it should take in a input string corresponding to a die array, as well as a number corresponding to the number of rolls left
    // it should then print out the expected value of the best move
    cout << "Welcome to yamslam, Please enter a die array and the number of rolls left in the form of a string, for example 12345 2 would be the die array 1, 2, 3, 4, 5 and 2 rolls left " << endl;
    string input;
    cin >> input;
    while (input != "quit") {
        // parse the input string into a vector of ints
        vector<int> die;
        for (int i = 0; i < input.length(); ++i) {
            die.push_back(input[i] - '0');
        }
        // update the die array in the board object
        for (int i = 0; i < die.size(); ++i) {
            if (die[i] == 1) {
                b.updateDie(d1, i);
            } else if (die[i] == 2) {
                b.updateDie(d2, i);
            } else if (die[i] == 3) {
                b.updateDie(d3, i);
            } else if (die[i] == 4) {
                b.updateDie(d4, i);
            } else if (die[i] == 5) {
                b.updateDie(d5, i);
            } else if (die[i] == 6) {
                b.updateDie(d6, i);
            }
        }
        cout << "Input the number of rolls left" << endl;
        cin >> rolls;
        // call bestExpectedValue and print out the expected value
        vector<double> result = bestExpectedValue(p1, b, rolls);
        cout << "The expected value of the best move is: " << endl;
        cout << result[result.size() - 1] << endl;
        for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " " << endl;
        }
        // get the next input string
        cin >> input;
    }
    
    // first create board, set to defualt, then make players
    // decide which player goes first and go to the left
    // play until all chips are gone then print out score and delete any objects
}