#pragma once

#include "pch.h"
#include "Dice.h"
#include "Player.h"

ref class Game {

public:
	// constructor
	Game();
	
	void Play();
	void PauseTurn();
	void WelcomePlayer();
	int GetNumPlayers();
	void GetRightLeftAndCurrentPlayer(Dice^ dice, Player^ player, cli::array<Player^>^ pArray, int roundNum, int currentPlayerNum, int numPlayers);
	void CheckChipsRollUpdateScores(Dice^ dice, Player^ player, cli::array<Player^>^ pArray, int cpNum, int rpNum, int lpNum);

	int roundNum = 0;
	int numRolls;
	int numPlayers;
	System::String^ userInput;
	
};


