/*
This source file is to implement the function of GameBase
*/

#include "stdafx.h"
#include "GameBase.h"
#include "NineAlmondsGame.h"
#include "MagicSquareGame.h"
#include "Reversi.h"

#include <utility>

using namespace std;

shared_ptr<GameBase> GameBase::sPtr = nullptr;

shared_ptr<GameBase> GameBase::instance() {
	if (sPtr == nullptr)
	{
		throw nullPtrError;
	}
	else
	{
		return sPtr;
	}
}


void GameBase::command(int argc, char* argv[]) {
	// check shared smart pointer
	if (sPtr != nullptr)
	{
		throw nullPtrError;
	}
	// check argument numbers
	if (argc == command_line_argument::expectedArguments)
	{
		// check command line
		//user input NineAlmonds
		if (argv[1] == string("NineAlmonds"))
		{
			sPtr = make_shared<NineAlmondsGame>();
			return;
		}
		//user input MagicSquare
		else if (argv[1] == string("MagicSquare"))
		{
			sPtr = make_shared<MagicSquareGame>();
			return;
		}
		else
		{
			cout << "Game Type Input Error!" << endl;
			throw gameTypeError;
		}
	}
	else if (argc == 3)
	{
		if (argv[1] == string("MagicSquare"))
		{
			istringstream iss(argv[2]);
			int dimension;
			if (iss >> dimension)
			{
				if (dimension < 1)
				{
					cout << "GameBoard dimesnion must be larger or equal to one" << endl;
					throw DimensionError;
				}
				else
				{
					sPtr = make_shared<MagicSquareGame>();
					sPtr->setNum(dimension);
					return;
				}
			}
			else
			{
				cout << "Second Argument must be a number" << endl;
				throw ArgumentError;
			}
		}
		else
		{
			cout << "First Argument Must be MagicSquare" << endl;
			throw gameTypeError;
		}
	}

	else if (argc == 4)
	{
		if (argv[1] == string("MagicSquare"))
		{
			istringstream iss1(argv[2]);
			istringstream iss2(argv[3]);
			int dimension;
			int start;
			if (iss1 >> dimension && iss2 >> start)
			{
				if (dimension < 1)
				{
					cout << "GameBoard dimesnion must be larger or equal to one" << endl;
					throw DimensionError;
				}
				else
				{
					sPtr = make_shared<MagicSquareGame>();
					sPtr->setNum(dimension);
					sPtr->setStartValue(start);
					return;
				}
			}
			else
			{
				cout << "Second and Third Argument must be a number" << endl;
				throw ArgumentError;
			}
		}
		else if (argv[1] == string("Reversi")) {
			string playerOne;
			string playerTwo;
			istringstream iss1(argv[2]);
			istringstream iss2(argv[3]);
			if (iss1 >> playerOne && iss2 >> playerTwo) {
				sPtr = make_shared<ReversiGame>();
				sPtr->setPlayerOne(playerOne);
				sPtr->setPlayerTwo(playerTwo);
				return;
			}
			else {
				cout << "Invalid UserName; Please Enter Valid Characters" << endl;
				throw Invalid_UserName;
			}
		}
		else
		{
			cout << "First Argument Must be MagicSquare" << endl;
			throw gameTypeError;
		}
	}
	else
	{
		cout << "Insufficient Argument Given!" << endl;
		throw not_enough_argu;
	}
}