//This is the GameImplementation.cpp File:

#include "GameTypes.h"
#include <cstdio>
#include <iostream>

//Constructor / Destructor
Game::Game() : _Player(NULL)
{
	this->Announcer();
	this->initBoard();

	//Allocation of _Player Array
	_Player = new Player*[2];

	if (this->Multiplayer()) {
		_Player[0] = new Human(this->getPlayerName(), XGlyph);
		_Player[1] = new Human(this->getPlayerName(), OGlyph);
	}
	else {
		_Player[0] = new Human(this->getPlayerName(), XGlyph);
		_Player[1] = new AI;
	}

	this->Pause();
}

Game::~Game()
{
	//Deallocation of _Player Array
	delete _Player[0];
	delete _Player[1];
	delete[] _Player;
}

//Accessors

//Utility Function for PrintBoard()
void printGlyphLine(const char* array, const int size)
{
	cout << " | ";

	for (int i = 0; i < size; i++) {
		cout << array[i];
	}
}

void Game::printBoard()
{
	//Reset Window...

	for (int i = 0; i < 5; i++)
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;

	cout << "\n     1     2     3   " << endl;
	cout <<   "  +-----+-----+-----+" << endl;

	//For each line of the GlyphArray
	for (int i = 0; i < 3; i++) {
		//Get the Glyph of each cell in the current line
		Glyph FirGlyph = this->Board[i][0];
		Glyph SecGlyph = this->Board[i][1];
		Glyph ThiGlyph = this->Board[i][2];

		//Print Line By Line
		for (int j = 0; j < 3; j++) {
			//Print Line Indicators...
			if (j == 1)
				cout << i + 1;
			else
				cout << " ";

			printGlyphLine(Glyphs[FirGlyph][j], 3);
			printGlyphLine(Glyphs[SecGlyph][j], 3);
			printGlyphLine(Glyphs[ThiGlyph][j], 3);

			cout << " |" << endl;
		}

		cout << "  +-----+-----+-----+" << endl;
	}

	cout << endl;
}

bool Game::boardIsFull() const
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (this->Board[i][j] == EmptyGlyph)
				return false;

	//Base Case
	return true;
}

//Functionality / Interactivity
void Game::Announcer()
{
	cout << " &&---------&&\n   TICTACTOE\n &&---------&&\n" << endl;
}

void Game::AnnouncerWin(Glyph Winner, Player& PlayerNo1, Player& PlayerNo2)
{
	if (Winner != EmptyGlyph) {
		cout << "//Game Over//: The Winner of the Match is: ";

		string WinnerName;

		if (Winner == XGlyph)
			WinnerName = PlayerNo1.getName();
		else
			WinnerName = PlayerNo2.getName();

		cout << WinnerName << endl;
	}
	else {
		cout << "//Game Over//: It's a Tie!" << endl;
	}
}

Glyph Game::Winner()
{
	//Check Horizontally
	for (int i = 0; i < 3; i++)
		if (this->Board[i][0] != EmptyGlyph)
			if (this->Board[i][0] == this->Board[i][1]
				&& this->Board[i][1] == this->Board[i][2])
					return this->Board[i][0];

	//Check Vertically
	for (int i = 0; i < 3; i++)
		if (this->Board[0][i] != EmptyGlyph)
			if (this->Board[0][i] == this->Board[1][i]
				&& this->Board[1][i] == this->Board[2][i])
					return this->Board[0][i];

	//Check Diagonally
	//Diagon A:
	if (this->Board[0][0] != EmptyGlyph)
		if (this->Board[0][0] == this->Board[1][1]
			&& this->Board[1][1] == this->Board[2][2])
				return this->Board[0][0];

	//Diagon B:
	if (this->Board[0][2] != EmptyGlyph)
		if (this->Board[0][2] == this->Board[1][1]
			&& this->Board[1][1] == this->Board[2][0])
				return this->Board[0][2];

	//Base Case
	return EmptyGlyph;
}

void Game::PlayGame()
{
	int Turn = 0;
	Glyph Winner;
	do {
		this->printBoard();

		if (!(Turn++ % 2)) {
			cout << this->_Player[0]->getName() << ", it's your turn." << endl;
			this->_Player[0]->performMove(*this);
		}
		else {
			cout << this->_Player[1]->getName() << ", it's your turn." << endl;
			this->_Player[1]->performMove(*this);
		}

		Winner = this->Winner();
	} while (Winner == EmptyGlyph && !this->boardIsFull());

	this->printBoard();
	this->AnnouncerWin(Winner, *_Player[0], *_Player[1]);
	this->Pause();
}

const string Game::getPlayerName() const
{
	string rStr;
	cout << "//Please enter your Name//: ";
	cin >> rStr;

	return rStr;
}

void Game::Pause() const
{
	//Clear input stream...
	cin.ignore(9999, '\n');

	cout << "\n______||PRESS ENTER TO CONTINUE||______\n" << endl;

	getchar();
}

bool Game::Multiplayer() const
{
	cout << "// Multiplayer ? (y / n) //: ";

	string input;
	cin >> input;

	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(9999, '\n');
		}
		else {
			if (input.compare("y") == 0 || input.compare("n") == 0)
				break;
		}

		cout << "//Please enter either 'y' or 'n'//: " << endl;
		cin >> input;
	}

	return ((input.compare("y") == 0) ? true : false);
}

//Mutators
void Game::initBoard()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			this->Board[i][j] = EmptyGlyph;
}