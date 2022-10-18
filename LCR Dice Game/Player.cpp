#include "pch.h"
#include "Player.h"

Player::Player() {
	
	SetPlayerName();
	chipCount = 3;
	hasChips = true;
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

void Player::WritePlayersToFile(System::String^ fileName, unsigned int roundNum, unsigned int playerNum) {

	System::IO::StreamWriter^ streamWriter = gcnew System::IO::StreamWriter(fileName);

	streamWriter->WriteLine("LCR Scores: \nFormat:\n\t\n\tName:\n\tRound {0}\n\tScore:\n\tStill in: (1 for yes, 0 for no)\n\nPlayers:",roundNum);

	for (unsigned int i = 0; i < playerNum; i++) {
		
		System::Console::WriteLine("Please enter player {0}'s name: ", (i + 1));
		SetPlayerName();

		streamWriter->WriteLine("\n\tName: {0}\n\tScore: {1}\n\tStill in: 1\n", name, chipCount);
	}

	streamWriter->Close();

}
void Player::EditFileUpdatedScores(System::String^ fileName, unsigned int currentRoundNum) {
	array<System::String^>^ args = System::Environment::GetCommandLineArgs();
	if (args->Length < 2)
	{
		//System::Console::WriteLine("\nUSAGE : file_info {0}\n\n", fileName);
		return;
	}
	
	System::IO::FileInfo^ fi = gcnew System::IO::FileInfo( args[1] );

	System::String^ roundNum = currentRoundNum.ToString();

	System::String^ stillIn = (hasChips) ? "1" : "0";
	System::String^ nameToReplace = ("\n\tName: {0}", name);
	System::String^ replaceWith = ("\n\tName: {0}\n\tRound {1}\n\tScore: {2}\n\tStill in: {3}\n", name, roundNum, chipCount, stillIn);
	
	fi->Replace(nameToReplace, replaceWith);
	
}


