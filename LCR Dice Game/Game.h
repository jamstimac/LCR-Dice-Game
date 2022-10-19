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
	void PauseTurn();
	void WelcomePlayer();
	int GetNumPlayers();
	void GetRightLeftAndCurrentPlayer(Dice^ dice, Player^ player,int roundNum, int currentPlayerNum, int numPlayers);
	void CheckChipsRollUpdateScores(int roundNum, Dice^ dice, Player^ player, System::IO::FileInfo^ fiCP, System::IO::FileInfo^ fiRP, System::IO::FileInfo^ fiLP);
	int GetChipCountReturnRolls(System::IO::FileInfo^ fiAffectedPlayer, Player^ player);

	// vairables
	int roundNum = 0;
	int numRolls;
	int numPlayers;
	System::String^ userInput;
	
};


