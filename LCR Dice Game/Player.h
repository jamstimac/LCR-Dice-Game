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
	void ChangeScores(int diceRoll, Player^ cPlayer, Player^ rPlayer, Player^ lPlayer);
	int ReturnEndLoop(cli::array<Player^>^ pArray, int playerNum);
	void WriteScoreToFile(int roundNum);

private:
	System::String^ name;
	int chipCount;
	bool hasChips;
};

