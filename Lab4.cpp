// Lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameBase.h"
#include "Header.h"
#include "NineAlmondsGame.h"
#include "Pieces.h"
#include "MagicSquareGame.h"
#include "Reversi.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	const char *programName = argv[command_line_argument::programName];

	GameBase *msg;
	shared_ptr<GameBase> pointer;
	try
	{
		msg->command(argc, argv);
	}
	catch (returnMessage rM)
	{
		usageMessage(programName);
		return rM;
	}

	try
	{
		pointer = msg->instance();
	}
	catch (returnMessage rM)
	{
		cout << "Null Pointer Found!" << endl;
		return rM;
	}
	int result = pointer->play();
	return result;
}
