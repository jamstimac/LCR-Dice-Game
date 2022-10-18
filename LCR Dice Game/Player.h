#pragma once

#include "pch.h"

ref class Player {
public:
	// constructor
	Player();
	Player(System::String^ enteredName, int chips);

	// functions
	void SetPlayerName();
	System::String^ GetPlayerName();
	void SetChipCount(unsigned int chips);
	unsigned int GetChipCount();
	void SetHasChips();
	bool GetHasChips();
	void CreatePlayerDirectory(System::String^ directoryName, int playerNum, unsigned int roundNum);
	void DeleteDirectory(System::String^ directoryName);
	void WritePlayersToFile(System::String^ fileName, unsigned int playerNum, int i);
	void WriteScoreToFile(System::String^ fileName, unsigned int roundNum, int i, Player^ currentPlayer);
	//void GetRightLeftCurrentPlayer(System::String^ fileName);
	//void EditFileUpdatedScores(System::String^ fileName, Player^ currentPlayer, Player^ rightPlayer, Player^ leftPlayer, unsigned int currentRoundNum);

private:
	System::String^ name;
	unsigned int chipCount;
	bool hasChips;
};

