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
	void ChangeScores(int diceRoll, int roundNum, System::IO::StreamReader^ srCP, System::IO::StreamReader^ srRP, System::IO::StreamReader^ srLP, System::IO::StreamWriter^ swCP, System::IO::StreamWriter^ swRP, System::IO::StreamWriter^ swLP);
	void WritePlayersToFile(System::String^ fullFilePath, int playerNum, int roundNum);
	void WriteScoreToFile(System::IO::StreamWriter^ swCP, int roundNum);
	void ReadInfoFromDirectoryFile(System::IO::StreamReader^ srCP);

private:
	System::String^ name;
	int chipCount;
	bool hasChips;
};

