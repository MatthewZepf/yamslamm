# Yamslam

Yamslam is a C++ implementation of the dice rolling game similar to Yahtzee. The goal is to recreate the Yamslam experience and determine the best die to roll recursively to maximize the expected value.

## Rules
The rules of Yamslam can be found [here](https://www.ultraboardgames.com/yamslam/game-rules.php).

## Implementation
The codebase consists of three main files:
- **Board.cpp**: Contains the implementation for managing the game board.
- **Dice.cpp**: Implements the behavior of the dice used in the game.
- **Player.cpp**: Implements the logic for player actions and decisions.

## Features
- Simulated and built a Yamslam game allowing users to play in the terminal and solve for the optimal move using expected values and Dynamic Programming.
- Utilized memoization and alpha-beta pruning techniques to greatly increase performance.
