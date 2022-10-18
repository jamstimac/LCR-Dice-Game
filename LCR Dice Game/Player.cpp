#include "pch.h"
#include "Player.h"

Player::Player(System::String^ enteredName, int chips) {
	System::Console::WriteLine("PLAYERR::.CTOR");
	name = enteredName;
	chipCount = chips;
	SetHasChips();
}

void Player::SetPlayerName() {
	name = System::Console::ReadLine();
}
void Player::EnterPlayerName(System::String^ enteredName) {
	name = enteredName;
}
System::String^ Player::GetPlayerName() {
	return name;
}
void Player::SetChipCount(int chips) {
	chipCount = chips;
}
unsigned int Player::GetChipCount() {
	return chipCount;
}
void Player::SetHasChips() {
	hasChips = (GetChipCount() >= 1);
}
void Player::EnterHasChips(bool zeroOrOne) {
	hasChips = zeroOrOne;
}
bool Player::GetHasChips() {
	return hasChips;
}

void Player::WriteFilesToPlayerDirectory(System::IO::DirectoryInfo^ di, int playerNum, int roundNum) {
	System::String^ fileName;
	for (int i = 0; i < playerNum; i++) {
		int currentPlayer = i + 1;
		fileName = ("{0}.txt", currentPlayer.ToString());

		WritePlayersToFile((DIRECTORY_NAME+PATH_TOKEN+fileName), i, roundNum);
	}
	
}	
void Player::DeleteDirectory() {
	// deletes directory at end of game
	System::IO::DirectoryInfo^ di = gcnew System::IO::DirectoryInfo(DIRECTORY_NAME);
	di->Delete();
}
void Player::WritePlayersToFile(System::String^ fileName, int playerNum, int roundNum) {
	/// Functionality pulled from 
	/// https://learn.microsoft.com/en-us/cpp/dotnet/file-handling-and-i-o-cpp-cli?view=msvc-170&viewFallbackFrom=vs-2017#retrieve
	
	System::IO::StreamWriter^ streamWriter = gcnew System::IO::StreamWriter(fileName);

	System::Console::WriteLine("Please enter player {0}'s name: ", (playerNum + 1));
	SetPlayerName();

	streamWriter->WriteLine("Round {0}\n\tPlayerNum: {1}\n\tName: {2}\n\tScore: {3}\n\tStill in: 1\n",roundNum, (playerNum+1), name, chipCount);

	streamWriter->Close();

}
void Player::ChangeScores(int diceRoll, Player^ player, System::IO::StreamWriter srCP, System::IO::StreamWriter srRP, System::IO::StreamWriter srLP) {
	int currentChips = this->GetChipCount();

	// rolled L
	if (diceRoll == 0) {
		// give one chip to player to left
		// take one chip from current player chip count
		currentChips--;
		// print dice
		System::Console::WriteLine("You gave a chip to the left, ");
		System::Console::WriteLine("Chip Count now: {0}\n", this->GetChipCount());
	}
	// rolled R
	else if (diceRoll == 1) {
		// give one chip to player to the right
		// take one chip from current player chip count
		currentChips--;
		// print dice
		System::Console::WriteLine("You gave a chip to the right, ");
		System::Console::WriteLine("Chip Count now: {0}\n", this->GetChipCount());
	}
	// rolled C
	else if (diceRoll == 2) {
		// take one chip from current player chip count
		currentChips--;
		// print dice
		System::Console::WriteLine("You gave a chip to the bank, ");
		System::Console::WriteLine("Chip Count now: {0}\n", this->GetChipCount());
	}
	// rolled * (no change to chip counts)
	else {
		// print dice
		System::Console::WriteLine("You still have {} chips.\n");
	}
	this->SetChipCount(currentChips);
	System::Console::WriteLine(currentChips.ToString());
}

void Player::WriteScoreToFile(System::String^ fileName, int playerNum, Player^ currentPlayer, int roundNum) {
	System::IO::StreamWriter^ streamWriter = gcnew System::IO::StreamWriter(fileName);

	int hasChips = (currentPlayer->GetHasChips()) ? 1 : 0;

	streamWriter->WriteLine("\n\nRound {0}\n\tPlayerNum: {1}\n\tName: {2}\n\tScore: {3}\n\tStill in: {4}\n", roundNum, (playerNum+1), currentPlayer->GetPlayerName(), currentPlayer->GetChipCount(), hasChips);
	
	streamWriter->Close();
}



