#pragma once

#include "pch.h"

ref class Player {
public:
	// constructor
	Player(System::String^ enteredName, int chips);

	// functions
	void SetPlayerName();
	void EnterPlayerName(System::String^ enteredName);
	System::String^ GetPlayerName();
	void EnterChipCount(int chips);
	unsigned int GetChipCount();
	void AddChip();
	void SubtractChip();
	void SetHasChips();
	void EnterHasChips(bool zeroOrOne);
	bool GetHasChips();
	int ReturnNumRolls();
	void WritePlayersToArray(array<Player^>^ parray, Player^ player, int playernum);
	void ChangeScores(int diceRollint diceRoll, cli::array<Player^>^ pArray, int cpNum, int rpNum, int lpNum);
	//void WriteScoreToFile(System::IO::StreamWriter^ swCP, int roundNum);

private:
	System::String^ name;
	int chipCount;
	bool hasChips;
};

