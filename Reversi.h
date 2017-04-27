#include "GameBase.h"

using namespace std;

class ReversiGame : public GameBase {
public:
	friend ostream& operator<< (ostream &os, const ReversiGame &rsg);

	void print();

	virtual bool done();

	virtual bool stalemate();

	virtual int prompt(unsigned int &a, unsigned int &b);

	virtual int turn();

	int play();

	void boardInit();

	// Check if there are valid move remained
	bool validMoveCheck(string s);
	bool validMoveCheckAtPosition(int x, int y, string s);

	// check valid move in eight different direction
	bool checkUp(int x, int y, string s, bool FlipOrNot);
	bool checkDown(int x, int y, string s, bool FlipOrNot);
	bool checkLeft(int x, int y, string s, bool FlipOrNot);
	bool checkRight(int x, int y, string s, bool FlipOrNot);
	bool checkUpLeft(int x, int y, string s, bool FlipOrNot);
	bool checkUpRight(int x, int y, string s, bool FlipOrNot);
	bool checkDownLeft(int x, int y, string s, bool FlipOrNot);
	bool checkDownRight(int x, int y, string s, bool FlipOrNot);

	// 1 or 2
	int playerTurn;

	void saveGameState(string s);

	// Flip
	void flipPieces(int x, int y);
};

ostream& operator<< (ostream &os, const ReversiGame &rsg);