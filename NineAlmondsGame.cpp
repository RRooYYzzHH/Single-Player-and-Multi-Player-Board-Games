#include "stdafx.h"
#include "NineAlmondsGame.h"

#include <utility>

using namespace std;

// Print out the Game Board
ostream & operator<< (ostream &os, const NineAlmondsGame & nag) {
	int height = nag.height;
	int width = nag.width;
	vector<vector<game_piece>> gameBoard = nag.gameBoard;
	for (int i = height - 1; i >= 0; i--) {
		os << i;
		for (int j = 0; j < width; j++) {
			os << setw(nag.longestLength + 1) << gameBoard[j][i].displayed;
		}
		os << endl;
		os << endl;
		if (i == 0)
		{
			os << "X 0 1 2 3 4" << endl;
		}
	}
	return os;
}

void NineAlmondsGame::print()
{
	cout << *this;
}

// Play Method
int NineAlmondsGame::play() {
	int turns = 0;

	// Ask if load the previous game state
	string loadFileName = "NineAlmonds.txt";
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
				string temp;
				int t;
				if (iss >> temp && iss >> t)
				{
					turns = t;
				}
				else {
					cout << "Saved Data Error!" << endl;
					return DataError;
				}

				for (int i = 0; i < width; i++)
				{
					for (int j = 0; j < height; j++)
					{
						gameBoard[i][j].displayed = " ";
					}
				}

				while (getline(ifs, firstLine))
				{
					int x;
					int y;
					istringstream iss2(firstLine);

					if (iss2 >> x && iss2 >> y)
					{
						// Out of Bound
						if (x < 0 || y < 0 || x >= width || y >= height) 
						{
							iss2.clear();
							continue;
						}

						gameBoard[x][y].displayed = "A";
					}
				}
			}
		}

		// User don't want to continue the previous game
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
		turns += 1;
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
			saveGameState(result, turns);

			cout << "The user played " << turns << " turns and then quit the game.." << endl;
			return user_quit;
		}
		// check done(); finish the game
		if (done())
		{
			cout << "The user used " << turns << " turns to complete the game.." << endl;
			return success;
		}
		// check stalemate(); no valid move remain
		cout << "3" << endl;
		if (stalemate())
		{
			cout << "The user played " << turns << " turns and no valid moves remain.." << endl;
			return no_valid_move_remain;
		}
	}
}

// Save Game State
void NineAlmondsGame::saveGameState(string s, int turns) {
	ofstream ofs;
	string saveFileName = "NineAlmonds.txt";
	ofs.open(saveFileName);

	// Save
	if (s == "y")
	{
		ofs << "Save Data " << turns << endl;

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (gameBoard[i][j].displayed == "A")
				{
					ofs << i << " " << j << endl;
				}
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

// Done Method
bool NineAlmondsGame::done() {
	bool result = true;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == (height - 1) / 2 && j == (width - 1) / 2 && gameBoard[j][i].displayed != "A")
			{
				return false;
			}
			if (i != (height - 1) / 2 && j != (width - 1) / 2 && gameBoard[j][i].displayed == "A")
			{
				return false;
			}
		}
	}
	return result;
}

// Stalemate Method
bool NineAlmondsGame::stalemate() {
	if (done())
	{
		return true;
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			string display = gameBoard[j][i].displayed;
			if (display == "A")
			{
				// totally 8 cases in 8 different directions
				if (j - 1 > 0)
				{
					if (gameBoard[j - 1][i].displayed == "A" && gameBoard[j - 2][i].displayed == " ")
					{
						return false;
					}
				}
				if (j + 1 < width - 1)
				{
					if (gameBoard[j + 1][i].displayed == "A" && gameBoard[j + 2][i].displayed == " ")
					{
						return false;
					}
				}
				if (i - 1 > 0)
				{
					if (gameBoard[j][i - 1].displayed == "A" && gameBoard[j][i - 2].displayed == " ")
					{
						return false;
					}
				}
				if (i + 1 < height - 1)
				{
					if (gameBoard[j][i + 1].displayed == "A" && gameBoard[j][i + 2].displayed == " ")
					{
						return false;
					}
				}
				if (j - 1 > 0 && i - 1 > 0)
				{
					if (gameBoard[j - 1][i - 1].displayed == "A" && gameBoard[j - 2][i - 2].displayed == " ")
					{
						return false;
					}
				}
				if (j - 1 > 0 && i + 1 < height - 1)
				{
					if (gameBoard[j - 1][i + 1].displayed == "A" && gameBoard[j - 2][i + 2].displayed == " ")
					{
						return false;
					}
				}
				if (j + 1 < width - 1 && i - 1 > 0)
				{
					if (gameBoard[j + 1][i - 1].displayed == "A" && gameBoard[j + 2][i - 2].displayed == " ")
					{
						return false;
					}
				}
				if (j + 1 < width - 1 && i + 1 < height - 1)
				{
					if (gameBoard[j + 1][i + 1].displayed == "A" && gameBoard[j + 2][i + 2].displayed == " ")
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

//Turn Method
int NineAlmondsGame::turn() {
	string print = "";
	int x_now, y_now;
	int temp = 0;
	while (true)
	{
		if (temp == 0)
		{
			cout << "Please select a starting square:" << endl;
		}
		else
		{
			cout << "Please select an ending square: (the square to move is " << x_now << "," << y_now << ")" << endl;
		}

		bool judge = true;
		while (judge)
		{
			unsigned int x = 1;
			unsigned int y = 1;
			int returnValue = prompt(x, y);
			// Quit 
			if (returnValue == 1)
			{
				return user_quit;
			}

			if (temp == 0)
			{
				if (gameBoard[x][y].displayed != "A")
				{
					cout << "Error: invalid starting square, the starting square needs to have a almond, please re-input!" << endl;
					continue;
				}
				x_now = x;
				y_now = y;
				print = to_string(x) + ',' + to_string(y) + ' ';
				break;
			}
			if (!checkPosition(x, y, x_now, y_now) || gameBoard[x][y].displayed != " " || gameBoard[(x + x_now) / 2][(y + y_now) / 2].displayed != "A")
			{
				cout << "Error: invalid ending square, no valid move, please re-input! "
					<< "(Square to move is " << x_now << "," << y_now << ")" << endl;

				continue;
			}

			gameBoard[x_now][y_now].displayed = " ";
			gameBoard[x][y].displayed = "A";
			gameBoard[(x + x_now) / 2][(y + y_now) / 2].displayed = " ";
			string print_tmp = print + "to " + to_string(x) + ',' + to_string(y) + ' ';
			cout << *this << endl;
			cout << print_tmp << endl;
			cout << endl;

			string ctr;
			while (true)
			{
				cout << "Continue this turn (YyNn)?" << endl;
				cin >> ctr;
				if (ctr == "N" || ctr == "n")
				{
					return success;
				}
				else if (ctr == "Y" || ctr == "y")
				{
					x_now = x;
					y_now = y;
					print = print_tmp;
					judge = false;
					break;
				}
				else {
					cout << "Error: invalid answer, please re-answer.." << endl;
					continue;
				}
			}

		}
		temp = 1;
	}
}

int NineAlmondsGame::prompt(unsigned int & first, unsigned int & second) {
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