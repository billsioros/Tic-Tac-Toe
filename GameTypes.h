//This is the GameTypes.h File:

#ifndef G_TYPES_H
#define G_TYPES_H

#include <string>

using namespace std;

//Forward Declarations...
class Player;

//Key Elements:

enum Glyph { XGlyph, OGlyph, EmptyGlyph };

const char Glyphs[3][3][3] = 
{
	//X Letter Glyph
	{
		{ '#', ' ', '#' },
		{ ' ', '#', ' ' },
		{ '#', ' ', '#' }
	},

	//O Letter Glyph
	{
		{ '#', '#', '#' },
		{ '#', ' ', '#' },
		{ '#', '#', '#' }
	},

	//Empty Glyph
	{
		{ ' ', ' ', ' ' },
		{ ' ', ' ', ' ' },
		{ ' ', ' ', ' ' }
	}
};

//Game Class
class Game {
private:
	Glyph Board[3][3];
	Player** _Player;

public:
	//Constructor / Destructor
	Game();
	~Game();

	//Accessors
	Glyph getGlyph(const int i, const int j) const { return this->Board[i][j]; }
	void printBoard();
	bool boardIsFull() const;

	//Functionality / Interactivity
	void Announcer();
	void AnnouncerWin(Glyph Winner, Player& PlayerNo1, Player& PlayerNo2);
	Glyph Winner();
	void PlayGame();
	const string getPlayerName() const;
	void Pause() const;
	bool Multiplayer() const;

	//Mutators
	void initBoard();
	void setGlyph(const int i, const int j, const Glyph SomeGlyph) { this->Board[i][j] = SomeGlyph; }
};

//Player Class
class Player {
protected:
	const string Name;
	const Glyph PlayerGlyph;

public:
	//Constructor
	Player(const string _Name, const Glyph _PlayerGlyph);

	//Accessors
	const string& getName() { return this->Name; }
	const Glyph& getSymbol() { return this->PlayerGlyph; }

	virtual void performMove(Game& thisGame) = 0;
};

//Human Subclass
class Human : public Player {
public:
	Human(const string _Name, const Glyph _PlayerGlyph) : Player(_Name, _PlayerGlyph) {}

	int GetInput() const;
	void performMove(Game& thisGame);
};

//AI Subclass

//Move Struct...
struct Move {
	Move() {}
	Move(int Score) : score(Score) {}

	int x;
	int y;
	int score;
};

class AI : public Player {
public:
	AI() : Player("AI", OGlyph) {}

	Move getBestMove(Game& thisGame, Glyph currentPlayer);
	void performMove(Game& thisGame);
};
#endif
