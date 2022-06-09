// Yamslam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Dice.h"
#include "Boardr.h"
#include "gamer.h"
#include "Player.h"
#include <algorithm>
#include <vector>
using namespace std;

void combinationUtil(int arr[], int data[],
    int start, int end,
    int index, int r, vector<vector<int>> &c, int &i);

// The main function that prints
// all combinations of size r
// in arr[] of size n. This function
// mainly uses combinationUtil()
vector<vector<int>> printCombination(int arr[], int n, const int r)
{
    // A temporary array to store
    // all combination one by one
    int* data = new int[n];
    vector<vector<int>> list (200, vector<int>(0,0));

    // Print all combination using
    // temporary array 'data[]'
    int i = 0;
    combinationUtil(arr, data, 0, n - 1, 0, r, list, i);
    delete[] data;
    return list;
}

/* arr[] ---> Input Array
data[] ---> Temporary array to
store current combination
start & end ---> Starting and
Ending indexes in arr[]
index ---> Current index in data[]
r ---> Size of a combination to be printed */
void combinationUtil(int arr[], int data[],
    int start, int end,
    int index, int r, vector<vector<int>> &c, int& z)
{
    // Current combination is ready
    // to be printed, print it
    if (index == r)
    {
        for (int j = r-1; j >= 0; j--) {
            c.at(z).push_back(data[j]);
        }
    }
    if (c.at(z).size() != 0) {
        z++;
    }
    // replace index with all possible
    // elements. The condition "end-i+1 >= r-index"
    // makes sure that including one element
    // at index will make a combination with
    // remaining elements at remaining positions
    for (int i = start; i <= end &&
        end - i + 1 >= r - index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i + 1,
            end, index + 1, r, c, z);
    }
}

//goes through all possible dice combinations and returns a vector with the highest expected value and the indices of the dice to roll which get that expected value
void bestExpectedValue(Player p, Board b, int NumberofRollsLeft, vector<int> &max) {
    int currentValue = p.bestCoinWithDice(b);
    if (NumberofRollsLeft == 0) {
        return;
    }
    else if (NumberofRollsLeft == 1) {
        //creates an array of ints of the die
        int valueArray[5] = { b.getDiceatIndex(0).getDieValue(), b.getDiceatIndex(1).getDieValue(), b.getDiceatIndex(2).getDieValue(), b.getDiceatIndex(3).getDieValue(), b.getDiceatIndex(4).getDieValue() };
        for (int i = 1; i <= 5; i++) {
            vector<vector<int>> combonations = printCombination(valueArray, 5, i);
            int counter = 0;
            while (combonations.at(counter).size() > 0) {
                for (int j = 0; j < combonations.at(counter).size(); j++) {
                    Dice temp[5];
                }

                counter++;
            }
        }
    }
    return;
}

int main() {
    int arr[5] = { 0,1,2,3,4 };
    const int r = 3;
    vector<vector<int>> combonations = printCombination(arr, 5, r);
    return 0;
    // first create board, set to defualt, then make players
    // decide which player goes first and go to the left
    // play until all chips are gone then print out score and delete any objects
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

