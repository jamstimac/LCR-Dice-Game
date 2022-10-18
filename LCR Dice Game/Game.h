#pragma once

#include "pch.h"

ref class Game {
public:
	// constructors
	Game();

	// functions
	void Play();
	void WelcomePlayer(System::String^ fileName);
	int GetNumPlayers();

	// vairables
	unsigned int numRolls;
	unsigned int numPlayers;
	System::String^ userInput;
	
};



