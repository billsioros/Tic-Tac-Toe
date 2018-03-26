//This is the PlayerImplementation.cpp File:

#include "GameTypes.h"
#include <iostream>
#include <vector>

//Constructor
Player::Player(const string _Name, const Glyph _PlayerGlyph) : Name(_Name), PlayerGlyph(_PlayerGlyph)
{
	cout << "\n//Player Info//: " << this->Name << " | " << (this->PlayerGlyph == XGlyph ? 'X' : 'O') << endl << endl;
}

//Human Subclass

int Human::GetInput() const
{
	int returnValue;
	cin >> returnValue;

	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(9999, '\n');
		}
		else {
			if (returnValue > 0 && returnValue < 4)
				break;
		}

		cout << "Please enter a number of integer Value Between 1 and 3" << endl;
		cin >> returnValue;
	}

	return returnValue;
}

void Human::performMove(Game& thisGame)
{
	int Y, X;

	do {
		cout << "//Y coordinate// : ";
		Y = this->GetInput();
		cout << "//X coordinate// : ";
		X = this->GetInput();

		if (thisGame.getGlyph(Y - 1, X - 1) != EmptyGlyph)
			cout << "\nERROR: //The cell is already taken//\n" << endl;
		else
			break;
	} while (true);

	thisGame.setGlyph(Y - 1, X - 1, this->PlayerGlyph);
}

//AI Subclass

//Static Variables...
const Glyph AI_Glyph = OGlyph;
const Glyph Human_Glyph = XGlyph;

Move AI::getBestMove(Game& thisGame, Glyph currentPlayer)
{
	//Base Case
	if (thisGame.Winner() == AI_Glyph)
		return Move(10);	//AI Win
	else if (thisGame.Winner() == Human_Glyph)
		return Move(-10);	//Human Win
	else if (thisGame.boardIsFull())
		return Move(0);		//Tie

	//If not the Base Case recursively search for a Base Case Scenario
	vector<Move> moves;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (thisGame.getGlyph(i, j) == EmptyGlyph) {
				//Create a temporary move object
				Move move;
				move.y = i;
				move.x = j;
				//Do this Move
				thisGame.setGlyph(i, j, currentPlayer);
				//Check it's Score
				move.score = this->getBestMove(thisGame, (currentPlayer == AI_Glyph ? Human_Glyph : AI_Glyph)).score;
				//Undo the Move
				thisGame.setGlyph(i, j, EmptyGlyph);
				moves.push_back(move);
			}
		}
	}

	int bestMoveIndex = 0;

	if (currentPlayer == AI_Glyph) {
		//Search for the biggest Move Score
		int maxScore = -10000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score > maxScore) {
				bestMoveIndex = i;
				maxScore = moves[i].score;
			}
		}
	}
	else {
		//Search for the smallest Move Score
		int minScore = 10000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score < minScore) {
				bestMoveIndex = i;
				minScore = moves[i].score;
			}
		}
	}

	return moves[bestMoveIndex];
}

void AI::performMove(Game& thisGame)
{
	Move move = this->getBestMove(thisGame, AI_Glyph);
	thisGame.setGlyph(move.y, move.x, AI_Glyph);
}