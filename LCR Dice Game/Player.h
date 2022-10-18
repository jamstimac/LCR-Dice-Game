#pragma once

#include "pch.h"

ref class Player {
public:
	// constructor
	Player();

	// functions
	void SetPlayerName();
	System::String^ GetPlayerName();
	void SetChipCount(unsigned int chips);
	unsigned int GetChipCount();
	void SetHasChips();
	bool GetHasChips();
	void WritePlayersToFile(System::String^ fileName, unsigned int roundNum, unsigned int playerNum);
	void EditFileUpdatedScores(System::String^, unsigned int currentRoundNum);

private:
	System::String^ name;
	unsigned int chipCount;
	bool hasChips;
};

