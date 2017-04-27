#include "stdafx.h"
#include "Pieces.h"

#include <string>

using namespace std;

string changeValueToColor(int colorValue) {
	if (colorValue == 1)
	{
		return "red";
	}
	else if (colorValue == 2)
	{
		return "black";
	}
	else if (colorValue == 3)
	{
		return "white";
	}
	else if (colorValue == 4)
	{
		return "can_not_find_color";
	}
	else
	{
		return " ";
	}
}

int changeColorToValue(string color) {
	string &colorPointer = color;
	changeToLowercase(colorPointer);
	if (color == "red")
	{
		return 1;
	}
	else if (color == "black")
	{
		return 2;
	}
	else if (color == "white")
	{
		return 3;
	}
	else if (color == " ") {
		return 5;
	}
	else
	{
		return 4;
	}
}