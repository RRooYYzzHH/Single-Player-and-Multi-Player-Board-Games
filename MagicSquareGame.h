#include "GameBase.h"
#define numPieces 9

using namespace std;

class MagicSquareGame : public GameBase {

private:

public:
	// Used for done() method; vert is the sum in vertical direction, hori is the sum in horizontal direction, and diag is two diagonal sum
	vector<int> vert;
	vector<int> hori;
	int diag[2];

	friend ostream& operator<< (ostream &os, const MagicSquareGame &msg);

	void print();

	virtual bool done();

	int play();

	virtual bool stalemate();

	virtual int turn();

	virtual void prompt(unsigned int &p);

	virtual int prompt(unsigned int &a, unsigned int &b);

	void boardInit(int dimension, int start);

	void saveGameState(string s);
};

ostream & operator<< (ostream &os, const MagicSquareGame & nag);
