#include "pch.h"
#include "Player.h"

Player::Player() {
	
	SetPlayerName();
	chipCount = 3;
	hasChips = true;
}

Player::Player(System::String^ enteredName, int chips) {
	name = enteredName;
	chipCount = chips;
	SetHasChips();
}

void Player::SetPlayerName() {
	name = System::Console::ReadLine();
}
System::String^ Player::GetPlayerName() {
	return name;
}
void Player::SetChipCount(unsigned int chips) {
	chipCount = chips;
}
unsigned int Player::GetChipCount() {
	return chipCount;
}
void Player::SetHasChips() {
	hasChips = (GetChipCount() >= 1);
}
bool Player::GetHasChips() {
	return hasChips;
}

void Player::CreatePlayerDirectory(System::String^ directoryName, int playerNum, unsigned int roundNum) {
	System::IO::DirectoryInfo^ di = gcnew System::IO::DirectoryInfo(directoryName);
	
	di->Create();
	System::String^ fileName;
	for (int i = 0; i < playerNum; i++) {
		int currentPlayer = i + 1;
		fileName = ("{0}.txt", currentPlayer.ToString());

		WritePlayersToFile((directoryName+"\\"+ fileName), roundNum, i);
	}
	
}
void Player::DeleteDirectory(System::String^ directoryName) {
	// deletes directory at end of game
	System::IO::DirectoryInfo^ di = gcnew System::IO::DirectoryInfo(directoryName);
	di->Delete();
}
void Player::WritePlayersToFile(System::String^ fileName, unsigned int roundNum, int i) {
	/// Functionality pulled from 
	/// https://learn.microsoft.com/en-us/cpp/dotnet/file-handling-and-i-o-cpp-cli?view=msvc-170&viewFallbackFrom=vs-2017#retrieve
	
	System::IO::StreamWriter^ streamWriter = gcnew System::IO::StreamWriter(fileName);

	streamWriter->WriteLine("LCR Scores:\m\nFormat:\n\tPlayerNum:\n\tName:\n\tScore:\n\tStill in: (1 for yes, 0 for no)\n\nRound {0}",roundNum);
	
	System::Console::WriteLine("Please enter player {0}'s name: ", (i + 1));
	SetPlayerName();

	streamWriter->WriteLine("\n\tPlayerNum: {0}\n\tName: {1}\n\tRound {2}\n\tScore: {3}\n\tStill in: 1\n", (i+1), name, roundNum, chipCount);

	streamWriter->Close();

}

void Player::WriteScoreToFile(System::String^ fileName, unsigned int roundNum, int i, Player^ currentPlayer) {
	System::IO::StreamWriter^ streamWriter = gcnew System::IO::StreamWriter(fileName);

	int hasChips = (currentPlayer->GetHasChips()) ? 1 : 0;

	streamWriter->WriteLine("\n\nRound {0}\n\tPlayerNum: {1}\n\tName: {2}\n\tScore: {3}\n\tStill in: {4}\n", roundNum, (i + 1), currentPlayer->GetPlayerName(), currentPlayer->GetChipCount(), hasChips);
	
	streamWriter->Close();
}
	//void GetRightLeftCurrentPlayer(System::String^ fileName, unsigned int currentPlayerNum) {

//}
//void Player::EditFileUpdatedScores(System::String^ fileName, Player^ currentPlayer, Player^ rightPlayer, Player^ leftPlayer, unsigned int currentRoundNum) {
	/// functionality pulled from
	/// 
	
//}


