#include "stdafx.h"
#include "Reversi.h"
#define ReversiDimension 8
#define InitX 3
#define InitY 3

using namespace std;

void ReversiGame::boardInit() {
	num = ReversiDimension;
	height = num;
	width = num;
	longestLength = 1;
	game_piece empty;
	empty.displayed = " ";

	// Initial Game Board; Empty first
	// (line1 is empty line)
	vector<game_piece> line1;
	for (int i = 0; i < width; i++)
	{
		line1.push_back(empty);
	}
	for (int i = 0; i < height; i++)
	{
		gameBoard.push_back(line1);
	}

	// Initial the four pieces
	gameBoard[InitX][InitY].displayed = "X";
	gameBoard[InitX + 1][InitY + 1].displayed = "X";
	gameBoard[InitX + 1][InitY].displayed = "O";
	gameBoard[InitX][InitY + 1].displayed = "O";

	playerTurn = 1;
}

ostream & operator<< (ostream &os, const ReversiGame & rsg) {
	int height = rsg.height;
	int width = rsg.width;
	vector<vector<game_piece>> gameBoard = rsg.gameBoard;
	for (int i = height - 1; i >= 0; i--) {
		os << i;
		for (int j = 0; j < width; j++) {
			os << setw(rsg.longestLength + 1) << gameBoard[j][i].displayed;
		}
		os << endl;
		os << endl;
		if (i == 0)
		{
			os << "X 0 1 2 3 4 5 6 7" << endl;
		}
	}
	return os;
}

void ReversiGame::print() {
	cout << *this;
}

bool ReversiGame::done() {
	if (validMoveCheck("O") || validMoveCheck("X"))
	{
		return false;
	}

	// Count Pieces
	int countO = 0;
	int countX = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (gameBoard[i][j].displayed == "O")
			{
				countO++;
			}
			else if (gameBoard[i][j].displayed == "X")
			{
				countX++;
			}
		}
	}

	// Compare Pieces
	if (countX > countO) {
		cout << p1 << " wins!" << endl;
		return true;
	}
	else if (countO > countX)
	{
		cout << p2 << " wins!" << endl;
		return true;
	}
	else {
		cout << "Game Ties!" << endl;
		return false;
	}
}

bool ReversiGame::stalemate() {
	// There are vaild moves remain
	if (validMoveCheck("O") || validMoveCheck("X"))
	{
		return false;
	}
	if (done())
	{
		return false;
	}
	// Game Ties
	else
	{
		print();
		return true;
	}
}

int ReversiGame::prompt(unsigned int &first, unsigned int &second) {
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
	return success;
}

int ReversiGame::turn() {
	string movePieces;
	if (playerTurn == 1)
	{
		movePieces = "X";
		cout << p1 << "'s Turn: (move " << movePieces << ")" << endl;
	}
	else if(playerTurn == 2)
	{
		movePieces = "O";
		cout << p2 << "'s Turn: (move " << movePieces << ")" << endl;
	}

	// No valid move remain
	if (!validMoveCheck(movePieces))
	{
		return No_Valid_Move_For_Player;
	}

	unsigned int x;
	unsigned int y;

	while (true)
	{
		cout << "Please select the square to fill in!" << endl;
		int returnValue = prompt(x, y);

		// User quit
		if (returnValue == user_quit)
		{
			return user_quit;
		}

		// Check Availability
		if (gameBoard[x][y].displayed != " ")
		{
			cout << "============ Your select square has been occupied, please re-select! ==============" << endl;
			continue;
		}

		// Check Valid Move
		bool checkValidMove = validMoveCheckAtPosition(x, y, movePieces);
		if (!checkValidMove)
		{
			cout << "============ Your select square is invalid, please re-select! ==============" << endl;
			continue;
		}
		
		// Flip opponent's pieces
		// Up Direction
		checkUp(x, y, movePieces, true);
		checkDown(x, y, movePieces, true);
		checkLeft(x, y, movePieces, true);
		checkRight(x, y, movePieces, true);
		checkUpLeft(x, y, movePieces, true);
		checkUpRight(x, y, movePieces, true);
		checkDownLeft(x, y, movePieces, true);
		checkDownRight(x, y, movePieces, true);

		return success;
	}
}

int ReversiGame::play() {
	boardInit();

	// Ask if load the previous game state
	string loadFileName = "Reversi " + p1 + " " + p2 + ".txt";
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
				int turn;
				if (iss >> temp && iss >> turn)
				{
					playerTurn = turn;
				}
				else {
					cout << "Saved Data Error!" << endl;
					return DataError;
				}

				// Empty the GameBoard
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
					string p;
					istringstream iss2(firstLine);

					if (iss2 >> x && iss2 >> y && iss2 >> p)
					{
						// Out of Bound
						if (x < 0 || y < 0 || x >= width || y >= height)
						{
							iss2.clear();
							continue;
						}

						gameBoard[x][y].displayed = p;
					}
				}
			}
		}

		// User don't want to continue the previous game
		else
		{
			cout << "=============== Starting a new game! ================" << endl;
		}
	}

	while (true)
	{
		cout << endl;
		print();
		cout << endl;
		int turnValue = turn();

		// check the return value of turn(); user quit
		if (turnValue == user_quit)
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

		if (turnValue == No_Valid_Move_For_Player)
		{
			if (playerTurn == 1)
			{
				cout << endl << "===============No Available Moves for " << p1 << " ================" << endl;
			}
			else
			{
				cout << endl << "===============No Available Moves for " << p2 << " ================" << endl;
			}
		}

		cout << "Swap Turn......" << endl;
		if (playerTurn == 1)
		{
			playerTurn = 2;
		}
		else
		{
			playerTurn = 1;
		}
	}
}

void ReversiGame::saveGameState(string s) {
	ofstream ofs;
	string saveFileName = "Reversi " + p1 + " " + p2 + ".txt";
	ofs.open(saveFileName);

	// Save
	if (s == "y")
	{
		ofs << "Save Data " << playerTurn << endl;

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


bool ReversiGame::validMoveCheck(string s) {
	for (int i = 0; i < width; i++) 
	{
		for (int j = 0; j < height; j++) 
		{
			// Check if it is empty
			if (gameBoard[i][j].displayed == " ") 
			{
				// check if this position is valid move
				if (validMoveCheckAtPosition(i, j, s)) 
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool ReversiGame::validMoveCheckAtPosition(int x, int y, string s) {
	if (checkUp(x, y, s, false) || checkDown(x, y, s, false) || checkLeft(x, y, s, false) || checkRight(x, y, s, false) || checkUpLeft(x, y, s, false) || checkUpRight(x, y, s, false) 
		|| checkDownLeft(x, y, s, false) || checkDownRight(x, y, s, false))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void ReversiGame::flipPieces(int x, int y) {
	if (gameBoard[x][y].displayed == "X")
	{
		gameBoard[x][y].displayed = "O";
	}
	else if (gameBoard[x][y].displayed == "O")
	{
		gameBoard[x][y].displayed = "X";
	}
}

bool ReversiGame::checkUp(int x, int y, string s, bool FlipOrNot) {
	bool result = false;
	// It y >= 6, no need to check further 
	if (y >= 6) 
	{
		return result;
	}

	int checkPosition = y + 1;
	int flipPosition;
	while (checkPosition <= 7)
	{
		// The first contiguous square
		if (checkPosition == y + 1)
		{
			// Contiguours is not opponent's piecces; not valid
			if (gameBoard[x][checkPosition].displayed == s || gameBoard[x][checkPosition].displayed == " ")
			{
				result = false;
				break;
			}
			// Do further check
			else
			{
				checkPosition++;
				continue;
			}
		}

		// Further Check
		else
		{
			if (gameBoard[x][checkPosition].displayed == s)
			{
				result = true;
				flipPosition = checkPosition;
				break;
			}
			else if (gameBoard[x][checkPosition].displayed == " ")
			{
				result = false;
				break;
			}
			else
			{
				checkPosition++;
				continue;
			}
		}
	}

	// No need to Flip
	if (!FlipOrNot) 
	{
		return result;
	}
	// Flip opponent's pieces
	else
	{
		// There is valid move
		if (result)
		{
			gameBoard[x][y].displayed = s;
			int flipStart = y + 1;
			while (flipStart < flipPosition)
			{
				flipPieces(x, flipStart);
				flipStart++;
			}
		}
	}

	return result;
}

bool ReversiGame::checkDown(int x, int y, string s, bool FlipOrNot) {
	bool result = false;
	// It y <= 1, no need to check further 
	if (y <= 1)
	{
		return result;
	}

	int checkPosition = y - 1;
	int flipPosition;
	while (checkPosition >= 0)
	{
		// The first contiguous square
		if (checkPosition == y - 1)
		{
			// Contiguours is not opponent's piecces; not valid
			if (gameBoard[x][checkPosition].displayed == s || gameBoard[x][checkPosition].displayed == " ")
			{
				result = false;
				break;
			}
			// Do further check
			else
			{
				checkPosition--;
				continue;
			}
		}

		// Further Check
		else
		{
			if (gameBoard[x][checkPosition].displayed == s)
			{
				result = true;
				flipPosition = checkPosition;
				break;
			}
			else if (gameBoard[x][checkPosition].displayed == " ")
			{
				result = false;
				break;
			}
			else
			{
				checkPosition--;
				continue;
			}
		}
	}

	// No need to Flip
	if (!FlipOrNot)
	{
		return result;
	}
	// Flip opponent's pieces
	else
	{
		// There is valid move
		if (result)
		{
			gameBoard[x][y].displayed = s;
			int flipStart = y - 1;
			while (flipStart > flipPosition)
			{
				flipPieces(x, flipStart);
				flipStart--;
			}
		}
	}

	return result;
}

bool ReversiGame::checkRight(int x, int y, string s, bool FlipOrNot) {
	bool result = false;
	// It x >= 6, no need to check further 
	if (x >= 6)
	{
		return result;
	}

	int checkPosition = x + 1;
	int flipPosition;
	while (checkPosition <= 7)
	{
		// The first contiguous square
		if (checkPosition == x + 1)
		{
			// Contiguours is not opponent's piecces; not valid
			if (gameBoard[checkPosition][y].displayed == s || gameBoard[checkPosition][y].displayed == " ")
			{
				result = false;
				break;
			}
			// Do further check
			else
			{
				checkPosition++;
				continue;
			}
		}

		// Further Check
		else
		{
			if (gameBoard[checkPosition][y].displayed == s)
			{
				result = true;
				flipPosition = checkPosition;
				break;
			}
			else if (gameBoard[checkPosition][y].displayed == " ")
			{
				result = false;
				break;
			}
			else
			{
				checkPosition++;
				continue;
			}
		}
	}

	// No need to Flip
	if (!FlipOrNot)
	{
		return result;
	}
	// Flip opponent's pieces
	else
	{
		// There is valid move
		if (result)
		{
			gameBoard[x][y].displayed = s;
			int flipStart = x + 1;
			while (flipStart < flipPosition)
			{
				flipPieces(flipStart, y);
				flipStart++;
			}
		}
	}

	return result;
}

bool ReversiGame::checkLeft(int x, int y, string s, bool FlipOrNot) {
	bool result = false;
	// It x <= 1, no need to check further 
	if (x <= 1)
	{
		return result;
	}

	int checkPosition = x - 1;
	int flipPosition;
	while (checkPosition >= 0)
	{
		// The first contiguous square
		if (checkPosition == x - 1)
		{
			// Contiguours is not opponent's piecces; not valid
			if (gameBoard[checkPosition][y].displayed == s || gameBoard[checkPosition][y].displayed == " ")
			{
				result = false;
				break;
			}
			// Do further check
			else
			{
				checkPosition--;
				continue;
			}
		}

		// Further Check
		else
		{
			if (gameBoard[checkPosition][y].displayed == s)
			{
				result = true;
				flipPosition = checkPosition;
				break;
			}
			else if (gameBoard[checkPosition][y].displayed == " ")
			{
				result = false;
				break;
			}
			else
			{
				checkPosition--;
				continue;
			}
		}
	}

	// No need to Flip
	if (!FlipOrNot)
	{
		return result;
	}
	// Flip opponent's pieces
	else
	{
		// There is valid move
		if (result)
		{
			gameBoard[x][y].displayed = s;
			int flipStart = x - 1;
			while (flipStart > flipPosition)
			{
				flipPieces(flipStart, y);
				flipStart--;
			}
		}
	}

	return result;
}

bool ReversiGame::checkUpLeft(int x, int y, string s, bool FlipOrNot) {
	bool result = false;
	// It y >= 6 or x <= 1, no need to check further 
	if (y >= 6 || x <= 1)
	{
		return result;
	}

	int checkPositionX = x - 1;
	int checkPositionY = y + 1;
	int xFlip;
	int yFlip;
	while (checkPositionY <= 7 && checkPositionX >= 0)
	{
		// The first contiguous square
		if (checkPositionY == y + 1 && checkPositionX == x - 1)
		{
			// Contiguours is not opponent's piecces; not valid
			if (gameBoard[checkPositionX][checkPositionY].displayed == s || gameBoard[checkPositionX][checkPositionY].displayed == " ")
			{
				result = false;
				break;
			}
			// Do further check
			else
			{
				checkPositionX--;
				checkPositionY++;
				continue;
			}
		}

		// Further Check
		else
		{
			if (gameBoard[checkPositionX][checkPositionY].displayed == s)
			{
				result = true;
				xFlip = checkPositionX;
				yFlip = checkPositionY;
				break;
			}
			else if (gameBoard[checkPositionX][checkPositionY].displayed == " ")
			{
				result = false;
				break;
			}
			else
			{
				checkPositionX--;
				checkPositionY++;
				continue;
			}
		}
	}

	// No need to Flip
	if (!FlipOrNot)
	{
		return result;
	}
	// Flip opponent's pieces
	else
	{
		// There is valid move
		if (result)
		{
			gameBoard[x][y].displayed = s;
			int xStart = x - 1;
			int yStart = y + 1;
			while (xStart > xFlip && yStart < yFlip)
			{
				flipPieces(xStart, yStart);
				xStart--;
				yStart++;
			}
		}
	}

	return result;
}

bool ReversiGame::checkUpRight(int x, int y, string s, bool FlipOrNot) {
	bool result = false;
	// It y >= 6 or x >= 6, no need to check further 
	if (y >= 6 || x >= 6)
	{
		return result;
	}

	int checkPositionX = x + 1;
	int checkPositionY = y + 1;
	int xFlip;
	int yFlip;
	while (checkPositionY <= 7 && checkPositionX <= 7)
	{
		// The first contiguous square
		if (checkPositionY == y + 1 && checkPositionX == x + 1)
		{
			// Contiguours is not opponent's piecces; not valid
			if (gameBoard[checkPositionX][checkPositionY].displayed == s || gameBoard[checkPositionX][checkPositionY].displayed == " ")
			{
				result = false;
				break;
			}
			// Do further check
			else
			{
				checkPositionX++;
				checkPositionY++;
				continue;
			}
		}

		// Further Check
		else
		{
			if (gameBoard[checkPositionX][checkPositionY].displayed == s)
			{
				result = true;
				xFlip = checkPositionX;
				yFlip = checkPositionY;
				break;
			}
			else if (gameBoard[checkPositionX][checkPositionY].displayed == " ")
			{
				result = false;
				break;
			}
			else
			{
				checkPositionX++;
				checkPositionY++;
				continue;
			}
		}
	}

	// No need to Flip
	if (!FlipOrNot)
	{
		return result;
	}
	// Flip opponent's pieces
	else
	{
		// There is valid move
		if (result)
		{
			gameBoard[x][y].displayed = s;
			int xStart = x + 1;
			int yStart = y + 1;
			while (xStart < xFlip && yStart < yFlip)
			{
				flipPieces(xStart, yStart);
				xStart++;
				yStart++;
			}
		}
	}

	return result;
}

bool ReversiGame::checkDownLeft(int x, int y, string s, bool FlipOrNot) {
	bool result = false;
	// It y <= 1 or x <= 1, no need to check further 
	if (y <= 1 || x <= 1)
	{
		return result;
	}

	int checkPositionX = x - 1;
	int checkPositionY = y - 1;
	int xFlip;
	int yFlip;
	while (checkPositionY >= 0 && checkPositionX >= 0)
	{
		// The first contiguous square
		if (checkPositionY == y - 1 && checkPositionX == x - 1)
		{
			// Contiguours is not opponent's piecces; not valid
			if (gameBoard[checkPositionX][checkPositionY].displayed == s || gameBoard[checkPositionX][checkPositionY].displayed == " ")
			{
				result = false;
				break;
			}
			// Do further check
			else
			{
				checkPositionX--;
				checkPositionY--;
				continue;
			}
		}

		// Further Check
		else
		{
			if (gameBoard[checkPositionX][checkPositionY].displayed == s)
			{
				result = true;
				xFlip = checkPositionX;
				yFlip = checkPositionY;
				break;
			}
			else if (gameBoard[checkPositionX][checkPositionY].displayed == " ")
			{
				result = false;
				break;
			}
			else
			{
				checkPositionX--;
				checkPositionY--;
				continue;
			}
		}
	}

	// No need to Flip
	if (!FlipOrNot)
	{
		return result;
	}
	// Flip opponent's pieces
	else
	{
		// There is valid move
		if (result)
		{
			gameBoard[x][y].displayed = s;
			int xStart = x - 1;
			int yStart = y - 1;
			while (xStart > xFlip && yStart > yFlip)
			{
				flipPieces(xStart, yStart);
				xStart--;
				yStart--;
			}
		}
	}

	return result;
}

bool ReversiGame::checkDownRight(int x, int y, string s, bool FlipOrNot) {
	bool result = false;
	// It y <= 1 or x >= 6, no need to check further 
	if (y <= 1 || x >= 6)
	{
		return result;
	}

	int checkPositionX = x + 1;
	int checkPositionY = y - 1;
	int xFlip;
	int yFlip;
	while (checkPositionY >= 0 && checkPositionX <= 7)
	{
		// The first contiguous square
		if (checkPositionY == y - 1 && checkPositionX == x + 1)
		{
			// Contiguours is not opponent's piecces; not valid
			if (gameBoard[checkPositionX][checkPositionY].displayed == s || gameBoard[checkPositionX][checkPositionY].displayed == " ")
			{
				result = false;
				break;
			}
			// Do further check
			else
			{
				checkPositionX++;
				checkPositionY--;
				continue;
			}
		}

		// Further Check
		else
		{
			if (gameBoard[checkPositionX][checkPositionY].displayed == s)
			{
				result = true;
				xFlip = checkPositionX;
				yFlip = checkPositionY;
				break;
			}
			else if (gameBoard[checkPositionX][checkPositionY].displayed == " ")
			{
				result = false;
				break;
			}
			else
			{
				checkPositionX++;
				checkPositionY--;
				continue;
			}
		}
	}

	// No need to Flip
	if (!FlipOrNot)
	{
		return result;
	}
	// Flip opponent's pieces
	else
	{
		// There is valid move
		if (result)
		{
			gameBoard[x][y].displayed = s;
			int xStart = x + 1;
			int yStart = y - 1;
			while (xStart < xFlip && yStart > yFlip)
			{
				flipPieces(xStart, yStart);
				xStart++;
				yStart--;
			}
		}
	}

	return result;
}