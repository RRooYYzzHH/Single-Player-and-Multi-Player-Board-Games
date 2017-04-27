#include "GameBase.h"

using namespace std;

class NineAlmondsGame : public GameBase {
private:

public:
	friend ostream & operator<< (ostream &os, const NineAlmondsGame & nag);

	void print();

	virtual bool done();

	virtual bool stalemate();

	virtual int turn();

	int play();

	virtual int prompt(unsigned int &, unsigned int &);

	NineAlmondsGame() {
		height = 5;
		width = 5;
		longestLength = 1;
		game_piece empty;
		game_piece A;
		empty.displayed = " ";
		A.displayed = "A";

		vector<game_piece> line1;
		vector<game_piece> line2;
		for (int i = 0; i < width; i++)
		{
			line1.push_back(empty);
			if (i == 0 || i == (width - 1))
			{
				line2.push_back(empty);
			}
			else
			{
				line2.push_back(A);
			}
		}
		for (int i = 0; i < height; i++)
		{
			if (i == 0 || i == (height - 1))
			{
				gameBoard.push_back(line1);
			}
			else
			{
				gameBoard.push_back(line2);
			}
		}
	}

	void saveGameState(string s, int turns);
};

ostream & operator<< (ostream &os, const NineAlmondsGame & nag);