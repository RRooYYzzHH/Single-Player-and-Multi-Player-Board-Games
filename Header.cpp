/*
This source file implements usageMessage function, which print out how to use my program
*/

#include "stdafx.h"
#include "header.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void usageMessage(const char *programName) {
	cout << "Usage: " << programName << " <Argument1> <Argument2> <Argument3>" << endl;
	cout << "Argument1 must be NineAlmonds or MagicSquare" << endl;
	cout << "Argument2 and Argument3 only available for MagicSquare Game; Both of them must be integer" << endl;
	cout << "Argument2 denotes the edge of the square game board" << endl;
	cout << "Argument3 denotes the start value of the game pieces" << endl;
}

void changeToLowercase(string &s) {
	int length = s.length();
	char tmp[1024];
	strcpy_s(tmp, s.c_str());
	for (int i = 0; i < length; i++) {
		int judge = int(tmp[i]);
		if (judge >= 65 && judge <= 90) {
			tmp[i] = int(tmp[i]) + 32;
		}
	}
	s = string(tmp);
}

// helper function
bool checkPosition(int x, int y, int x_now, int y_now) {
	if (x - x_now == 2 || x - x_now == -2)
	{
		if (y - y_now == 2 || y - y_now == -2 || y == y_now)
		{
			return true;
		}
		else {
			return false;
		}
	}
	else if (y - y_now == 2 || y - y_now == -2)
	{
		if (x - x_now == 2 || x - x_now == -2 || x == x_now)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

int lengthOfInteger(int i) {
	int result = 0;
	if (i < 0)
	{
		i = 0 - i;
		result++;
	}
	while (i)
	{
		result++;
		i = i / 10;
	}
	return result;
}