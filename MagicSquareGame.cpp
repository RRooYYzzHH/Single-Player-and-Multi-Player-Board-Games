#include "stdafx.h"
#include "MagicSquareGame.h"

#define magicSum 15
#define quitValue -999
#define defaultDimension 3
#define defaultStartValue 1

#include <utility>

using namespace std;

// Initialize the Magic Square Game
void MagicSquareGame::boardInit(int dimension, int startValue) {
	num = dimension;
	start = startValue;
	height = num;
	width = num;
	longestLength = 1;
	game_piece empty;
	empty.displayed = " ";

	// Initial sum
	for (int i = 0; i < width; i++)
	{
		vert.push_back(0);
		hori.push_back(0);
	}
	diag[0] = 0;
	diag[1] = 0;

	// Initial Game Board; Empty first
	vector<game_piece> line1;
	for (int i = 0; i < width; i++)
	{
		line1.push_back(empty);
	}
	for (int i = 0; i < height; i++)
	{
		gameBoard.push_back(line1);
	}

	// Initial the available pieces vector
	int numOfPiece = height * width;
	int l = 0;
	for (int i = 1; i <= numOfPiece; i++)
	{
		aP.push_back(start + i - 1);
	}
	// Initial the longest number
	for (int i = 0; i < aP.size(); i++)
	{
		int length = lengthOfInteger(aP[i]);
		if (length > l)
		{
			l = length;
		}
	}
	longestLength = l;
}

// Print out the Game Board
ostream & operator<< (ostream &os, const MagicSquareGame & mag) {
	int height = mag.height;
	int width = mag.width;
	vector<vector<game_piece>> gameBoard = mag.gameBoard;
	for (int i = height - 1; i >= 0; i--) {
		os << i;
		for (int j = 0; j < width; j++) {
			os << setw(mag.longestLength + 1) << gameBoard[j][i].displayed;
		}
		os << endl;
		os << endl;
		if (i == 0)
		{
			os << "X";
			for (int k = 0; k < width; k++)
			{
				os << setw(mag.longestLength + 1) << k;
			}
			os << endl;
		}
	}
	os << endl;
	os << "Available Pieces:";
	// print out the available pieces
	for (int i = 0; i < mag.aP.size(); i++)
	{
		os << setw(mag.longestLength + 1) << mag.aP[i];
	}
	os << endl;
	return os;
}

// Print Method
void MagicSquareGame::print()
{
	cout << *this;
}

// Done Method
bool MagicSquareGame::done() {
	// Check if any piece left
	if (aP.size() > 0)
	{
		return false;
	}
	// Check vertical sum
	for (int x = 0; x < width - 1; x++)
	{
		if (vert[x] != vert[x + 1])
		{
			return false;
		}
	}
	// Check horizontal sum
	for (int y = 0; y < height - 1; y++)
	{
		if (hori[y] != hori[y + 1])
		{
			return false;
		}
	}
	// Check diagonal sum
	if (diag[0] != diag[1])
	{
		return false;
	}
	else
	{
		if (diag[0] == vert[0] && diag[0] == hori[0])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

// Stalemate Method
bool MagicSquareGame::stalemate() {
	if (aP.size() == 0 && !done())
	{
		return true;
	}
	return false;
}

// Prompt
void MagicSquareGame::prompt(unsigned int &p) {
	bool conti = true;
	while (conti)
	{
		cout << "Please either input 'quit' to end the game or pick an available piece..." << endl;
		string input;
		cin >> input;
		if (input.empty())
		{
			cout << "Invalid Input!(Empty); Please re-input" << endl;
			continue;
		}
		else if (input == "quit")
		{
			throw quitValue;
			return;
		}
		else
		{
			istringstream iss(input);
			int value;
			if (iss >> value)
			{
				auto it = find(aP.begin(), aP.end(), value);
				if (it == aP.end())
				{
					cout << "Invalid Piece; Please Re-select" << endl;
					continue;
				}
				else
				{
					aP.erase(it);
					p = value;
					return;
				}
			}
			else
			{
				cout << "Sorry, you must input a valid number!" << endl;
				continue;
			}
		}
		conti = false;
	}
}

int MagicSquareGame::prompt(unsigned int & first, unsigned int & second) {
	bool conti = true;
	while (conti)
	{
		cout << "Hint: you can either input 'quit' to end the game or input a valid comma-separated coordinate.." << endl;
		string input;
		cin >> input;
		if (input == "quit")
		{
			return user_quit;
		}
		int validCheck = 0;
		int coma = 0;
		int size = input.size();
		char inputArray[1024];
		strcpy_s(inputArray, input.c_str());
		for (int i = 0; i < size; i++)
		{
			if (!isdigit(inputArray[i]) && inputArray[i] != ',')
			{
				validCheck += 1;
			}
			if (inputArray[i] == ',') {
				coma += 1;
				inputArray[i] = ' ';
			}
		}
		if (validCheck > 0 || coma != 1) {
			cout << "Your input is unvalid, please re-input.." << endl;
			continue;
		}
		input = string(inputArray);
		istringstream iss(input);
		int f, s;
		iss >> f;
		iss >> s;
		if (f < 0 || f >(width - 1) || s < 0 || s >(height - 1))
		{
			cout << "Your input is out of the game board, please re-input.." << endl;
			continue;
		}
		first = f;
		second = s;
		conti = false;
	}
	return 0;
}


//Turn Method
int MagicSquareGame::turn() {
	while (true)
	{
		cout << "Please select the square to fill in!" << endl;
		unsigned int x;
		unsigned int y;
		int returnValue = prompt(x, y);
		if (returnValue == user_quit)
		{
			return user_quit;
		}
		if (gameBoard[x][y].displayed != " ")
		{
			cout << "Your select piece has been occupied, please re-select!" << endl;
			continue;
		}
		unsigned int p;
		try
		{
			prompt(p);
		}
		catch (int i) {
			cout << "User quit when selecting the piece!" << endl;
			return user_quit;
		}

		int w = x;
		int h = y;

		// Deal with the vert sum, hori sum, and diag sum
		vert[w] += p;
		hori[h] += p;

		if ((w == 0 && h == 0) || (w == (width - 1) && (h == (height - 1))))
		{
			diag[0] += p;
		}
		else if ((w == 0 && h == (height - 1)) || (w == (width - 1) && h == 0))
		{
			diag[1] += p;
		}
		else if (w == (width - 1) / 2 && h == (height - 1) / 2)
		{
			diag[0] += p;
			diag[1] += p;
		}
		gameBoard[w][h].value = p;
		gameBoard[w][h].displayed = to_string(p);
		gameBoard[w][h].name = to_string(p);
		return success;
	}
}

// Play Method
int MagicSquareGame::play() {
	boardInit(num, start);

	// Ask if load the previous game state
	string loadFileName = "MagicSquare " + to_string(num) + " " + to_string(start) + ".txt";
	ifstream ifs(loadFileName);

	// Check if there exist game state
	if (ifs.is_open())
	{
		cout << "Save File Exist! Do you want to continue the previous game? (y/n):" << endl;
		string res;
		cin >> res;
		while (res != "y" && res != "n")
		{
			cout << "Save File Exist! Do you want to continue the previous game? (y/n):" << endl;
			cin >> res;
		}

		// If user want to continue
		if (res == "y") {
			string firstLine;
			getline(ifs, firstLine);
			istringstream iss(firstLine);
			string firstWord;
			iss >> firstWord;
			if (firstWord == "No")
			{
				cout << "Save File is Empty; We will start a new game!" << endl;
			}
			else
			{
				while (getline(ifs, firstLine))
				{
					int x;
					int y;
					int value;
					istringstream iss2(firstLine);
					if (iss2 >> x && iss2 >> y && iss2 >> value)
					{
						// Out of bound
						if (x >= num || y >= num || x < 0 || y < 0)
						{
							iss2.clear();
							continue;
						}

						// Search the value of pieces
						auto it = find(aP.begin(), aP.end(), value);
						if (it == aP.end())
						{
							continue;
						}
						aP.erase(it);

						gameBoard[x][y].value = value;
						gameBoard[x][y].displayed = to_string(value);
						gameBoard[x][y].name = to_string(value);

						int w = x;
						int h = y;

						// Deal with the vert sum, hori sum, and diag sum
						vert[w] += value;
						hori[h] += value;

						if (w == h)
						{
							diag[0] += value;
						}
						else if (w + h == num - 1)
						{
							diag[1] += value;
						}
					}
				}
			}
		}
		else
		{
			cout << "Starting a new game!" << endl;
		}
	}

	while (true)
	{

		cout << endl;
		print();
		cout << endl;
		int turnValue = turn();

		// check the return value of turn(); user quit
		if (turnValue == 1)
		{
			// Save Game
			cout << "Do you want to save current gameState? (y/n):";
			string result;
			cin >> result;
			while (result != "y" && result != "n") 			
			{
				cout << "Do you want to save current gameState? (y/n):";
				cin >> result;
			}
			saveGameState(result);


			cout << "The user quit the game.." << endl;
			return user_quit;
		}
		// check done(); finish the game
		if (done())
		{
			cout << "The user completes the game.." << endl;
			return success;
		}
		// check stalemate(); no valid move remain
		if (stalemate())
		{
			cout << "No valid move remain.." << endl;
			return no_valid_move_remain;
		}
	}
}

void MagicSquareGame::saveGameState(string s) {
	ofstream ofs;
	string saveFileName = "MagicSquare " + to_string(num) + " " + to_string(start) + ".txt";
	ofs.open(saveFileName);
	
	// Save
	if (s == "y") 
	{
		ofs << "Save Data" << endl;

		for (int i = 0; i < width; i++) 
		{
			for (int j = 0; j < height; j++)
			{
				ofs << i << " " << j << " " << gameBoard[i][j].displayed << endl;
			}
		}

		ofs.close();
	}
	// Not Save
	else
	{
		ofs << "No Data" << endl;
		ofs.close();
	}
}