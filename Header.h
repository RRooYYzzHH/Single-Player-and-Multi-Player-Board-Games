/*
We can consider this header file as support file.

First, this header file contains two enumrations, including command_line_argument and return message. And there are totally 5 different messages for our program.

Second, this header file also contains one usageMessage function:
usageMessage (handle the usage message)
*/

#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <istream>
#include <iomanip>
#include <memory>

using namespace std;

enum command_line_argument { programName, fileName, expectedArguments = 2, expectedAutoPlayArguments = 3 };

enum returnMessage
{
	success = 0,
	user_quit = 1,
	no_valid_move_remain = 2,
	error_command_line = 3,
	nullPtrError = 4,
	not_enough_argu = 5,
	gameTypeError = 6,
	DimensionError = 7,
	ArgumentError = 8,
	Invalid_UserName = 9,
	DataError = 10,
	No_Valid_Move_For_Player = 11
};

// Function prototypes
void usageMessage(const char *programName);

void changeToLowercase(string &s);

bool checkPosition(int x, int y, int x_now, int y_now);

int lengthOfInteger(int i);

#endif#pragma once
