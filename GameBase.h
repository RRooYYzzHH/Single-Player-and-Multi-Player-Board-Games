/*
This file is main header file of my program.

Fisrt, I define the class for our game board, which is NineAlmondsGame. It has 3 private variables, including width(equals to 5), height(equals to 5) and a two-dimensional string array(game board).
The class also has seven functions:
1. NineAlmondsGame(). This is the constructor function and initialize the game board array.
2. operator<<. This function is to print out the whole game board.
3. done
4. stalemate
5. prompt
6. turn
7. play
(functions 3 to 7 just follows the project requirement)

Apart from the class, I also implement a helper function checkPosition, which takes 4 integers and return a bool value. This function is to help me judge whethen two positions can be valid-move.
*/

#pragma once

#include "Header.h"
#include "Pieces.h"

using namespace std;

class GameBase {

protected:
	int width;
	int height;

	// This is the game board, which is a two-dimensional vector; game_piece is defined in "Piece.h"
	vector<vector<game_piece>> gameBoard;

	int longestLength = 0;
	// num is dimension and start is the starting number of pieces
	int num = 3;
	int start = 1;

	// Available Pieces, which contains all the number of available pieces
	vector<int> aP;

	static shared_ptr<GameBase> sPtr;

	// Player
	string p1;
	string p2;

public:
	//GameBase();

	void setLongestLength(int l) {
		longestLength = l;
	}

	// Set Player Name (Reversi Game)
	void setPlayerOne(string x) {
		p1 = x;
	}

	void setPlayerTwo(string x) {
		p2 = x;
	}

	virtual void print() = 0;

	// Base Class Method
	virtual bool done() = 0;

	virtual bool stalemate() = 0;

	virtual int turn() = 0;

	virtual int play() = 0;

	virtual int prompt(unsigned int &, unsigned int &) = 0;

	// PartII - 16
	static void command(int argc, char* argv[]);

	// Instance method
	static shared_ptr<GameBase> instance();

	void setNum(int n)
	{
		num = n;
	}

	void setStartValue(int x)
	{
		start = x;
	}
};



