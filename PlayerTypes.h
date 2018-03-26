//This is the PlayerTypes.h File:

#ifndef PLAYER_H
#define PLAYER_H

#include "BoardTypes.h"
#include <string>

class Player {
private:
	const std::string Name;
	const Glyph PlayerGlyph;

public:
	//Constructor
	Player(const std::string _Name, const Glyph _PlayerGlyph);

	//Accessors
	const std::string& getName() { return this->Name; }
	const Glyph& getSymbol() { return this->PlayerGlyph; }

	//Functionality / Interactivity
	//Human Player:
	int GetInput() const;
	void performMove(Game& thisGame) const;
};

#endif
