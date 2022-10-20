#include "pch.h"
#include "Player.h"

Player::Player(System::String^ enteredName, int chips) {
	System::Console::WriteLine("PLAYERR::.CTOR");
	name = enteredName;
	chipCount = chips;
	SetHasChips();
}

// System::String^ playerName mutator function through userInput
void Player::SetPlayerName() {
	name = System::Console::ReadLine();
}
// System::String^ playerName mutator function
void Player::EnterPlayerName(System::String^ enteredName) {
	name = enteredName;
}
// System::String^ playerName accessor function
System::String^ Player::GetPlayerName() {
	return name;
}
// int chipCount mutator function
void Player::EnterChipCount(int chips) {
	chipCount = chips;
}
// int chipCount acessor function
unsigned int Player::GetChipCount() {
	return chipCount;
}
// int chipCount quick add 1 function
void Player::AddChip() {
	chipCount += 1;
}
// int chipCount quick subtract 1 function
void Player::SubtractChip() {
	chipCount -= 1;
}

// bool hasChips mutator function through GetChipCount()
void Player::SetHasChips() {
	hasChips = (GetChipCount() >= 1);
}
// bool hasChips mutator function through entered bool
void Player::EnterHasChips(bool zeroOrOne) {
	hasChips = zeroOrOne;
}
// bool hasChips acessor function
bool Player::GetHasChips() {
	return hasChips;
}

// checks current player nums chips returns up to 3 rolls
int Player::ReturnNumRolls() {
	int rolls = GetChipCount() > 3) ? 3 : GetChipCount();
	return rolls;
}

// takes array and adds player objects to array with starting info including Name, chipCount=3, and hasChips=true
void Player::WritePlayersToArray(array<Player^>^ pArray, Player^ player, int playerNum) {
	System::Console::WriteLine("PLAYER::WRITEPLAYERSTOARRAY");
	for (int i = 0; i < playerNum; i++) {
		System::Console::WriteLine("\nPlease enter player {0}'s name: ", (i + 1));

		SetPlayerName();
		EnterChipCount(3);
		SetHasChips();

		pArray[i] = player;
		System::Console::WriteLine("ChipCount: {0}\nName: {1}\nHasChips: {2}", pArray[i]->GetChipCount(), pArray[i]->GetPlayerName(), pArray[i]->GetHasChips());
	}
}


// gets current scores, rolls dice, affects score changes
void Player::ChangeScores(int diceRoll, cli::array<Player^>^ pArray, int cpNum, int rpNum, int lpNum) {
//	System::Console::WriteLine("PLAYER::CHANGESCORES");
//	int currentChips = GetChipCount();
//	
//	// rolled L
//	if (diceRoll == 0) {
//		System::Console::WriteLine("Changing Right Player Chips");
//		ReadInfoFromDirectoryFile(srLP);
//		SetChipCount(GetChipCount() + 1);
//		WriteScoreToFile(swLP, roundNum);
//		// take one chip from current player chip count
//		System::Console::WriteLine("Changing Current Player Chips");
//		ReadInfoFromDirectoryFile(srCP);
//		currentChips--;
//		WriteScoreToFile(swCP, roundNum);
//		// print dice
//		System::Console::WriteLine("You gave a chip to the left, ");
//		System::Console::WriteLine("Chip Count now: {0}\n", GetChipCount());
//	}
//	// rolled R
//	else if (diceRoll == 1) {
//		ReadInfoFromDirectoryFile(srRP);
//		SetChipCount(GetChipCount() + 1);
//		WriteScoreToFile(swRP, roundNum);
//		// take one chip from current player chip count
//		ReadInfoFromDirectoryFile(srCP);
//		currentChips--;
//		WriteScoreToFile(swCP, roundNum);
//		// print dice
//		System::Console::WriteLine("You gave a chip to the right, ");
//		System::Console::WriteLine("Chip Count now: {0}\n", GetChipCount());
//	}
//	// rolled C
//	else if (diceRoll == 2) {
//		// take one chip from current player chip count
//		ReadInfoFromDirectoryFile(srCP);
//		currentChips--;
//		WriteScoreToFile(swCP, roundNum);
//		// print dice
//		System::Console::WriteLine("You gave a chip to the bank, ");
//		System::Console::WriteLine("Chip Count now: {0}\n", GetChipCount());
//	}
//	// rolled * (no change to chip counts)
//	else {
//		// print dice
//		System::Console::WriteLine("You still have {0} chips.\n", GetChipCount());
//	}
//}

// takes scores and winner and writes them to save file (functionality can be added later to retrieve save information)
//void Player::WriteScoreToFile(System::IO::StreamWriter^ swCP, int roundNum) {
//	System::Console::WriteLine("PLAYER::WRITESCORETOFILE");
//	int hasChips = (GetHasChips()) ? 1 : 0;
//	System::String^ line = ("Round {0}\n\tName: {2}\n\tScore: {3}\n\tStill in : {4}\n", roundNum, GetPlayerName(), GetChipCount(), hasChips.ToString());
//	swCP->WriteLine(line);
//	
//
//}