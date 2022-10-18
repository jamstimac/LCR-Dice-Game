#pragma once

#include "pch.h"
#include "Dice.h"
#include "Player.h"

ref class Game {

public:
	// constructors
	Game();

	// functions
	void Play();
	void PassTurn();
	void WelcomePlayer(System::String^ fileName);
	int GetNumPlayers();
	void GetRightLeftAndCurrentPlayer(char diceArray[], System::IO::DirectoryInfo^ di, Dice^ dice, Player^ player, int currentPlayerNum, int numPlayers);
	void CheckChipsRollUpdateScores(char diceArray[], Dice^ dice, Player^ player, System::IO::StreamReader^ srCP, System::IO::StreamReader^ srRP, System::IO::StreamReader^ srLP);
	int GetChipCountReturnRolls(System::IO::StreamReader^ srAffectedPlayer, Player^ player);

	// vairables
	int roundNum = 0;
	int numRolls;
	int numPlayers;
	System::String^ userInput;
	
};


