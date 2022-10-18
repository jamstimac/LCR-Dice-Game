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
	void SetChipCount(int chips);
	unsigned int GetChipCount();
	void SetHasChips();
	void EnterHasChips(bool zeroOrOne);
	bool GetHasChips();
	void WriteFilesToPlayerDirectory(System::IO::DirectoryInfo^ di, int playerNum, int roundNum);
	void DeleteDirectory();
	void ChangeScores(int diceRoll,Player^ player, System::IO::StreamWriter srCP, System::IO::StreamWriter srRP, System::IO::StreamWriter srLP);
	void WritePlayersToFile(System::String^ fileName, int i, int roundNum);
	void WriteScoreToFile(System::String^ fileName, int i, Player^ currentPlayer, int roundNum);
	
private:
	System::String^ name;
	int chipCount;
	bool hasChips;
};

