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
	void CheckChipsRollUpdateScores(int roundNum, Dice^ dice, Player^ player, System::IO::StreamReader^ srCP, System::IO::StreamReader^ srRP, System::IO::StreamReader^ srLP, System::IO::StreamWriter^ swCP, System::IO::StreamWriter^ swRP, System::IO::StreamWriter^ swLP);
	int GetChipCountReturnRolls(System::IO::StreamReader^ srCP, Player^ player);

	// vairables
	int roundNum = 0;
	int numRolls;
	int numPlayers;
	System::String^ userInput;
	
};


