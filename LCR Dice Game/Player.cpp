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

void Player::DeleteDirectory() {
	// deletes directory at end of game
	System::IO::DirectoryInfo^ di = gcnew System::IO::DirectoryInfo(DIRECTORY_NAME);
	di->Delete();
}
void Player::WriteFilesToPlayerDirectory(System::IO::DirectoryInfo^ di, int playerNum, int roundNum) {
	System::Console::WriteLine("PLAYER::WRITEFILESTOPLAYERDIRECTORY");
	System::String^ fileName;
	System::String^ roundFolderDir;
	for (int i = 0; i < playerNum; i++) {
		int currentPlayer = i + 1;
		fileName = ("{0}.txt", currentPlayer.ToString());
		roundFolderDir =ROUND+(roundNum.ToString());
		WritePlayersToFile((DIRECTORY_NAME + PATH_TOKEN + roundFolderDir + PATH_TOKEN +fileName), i, roundNum);
	}
	
}
void Player::WritePlayersToFile(System::String^ fullFilePath,int playerNum, int roundNum) {
	/// Functionality pulled from 
	/// https://learn.microsoft.com/en-us/cpp/dotnet/file-handling-and-i-o-cpp-cli?view=msvc-170&viewFallbackFrom=vs-2017#retrieve
	System::Console::WriteLine("PLAYER::WRITEPLAYERSTOFILE");
	System::IO::StreamWriter^ streamWriter = gcnew System::IO::StreamWriter(fullFilePath);

	System::Console::WriteLine("\nPlease enter player {0}'s name: ", (playerNum + 1));
	SetPlayerName();

	streamWriter->WriteLine("Round {0}\n\tName: {1}\n\tScore: {2}\n\tStill in: 1\n",roundNum.ToString(), GetPlayerName(), GetChipCount().ToString());

	streamWriter->Close();

}

void Player::WriteScoreToFile(System::IO::StreamWriter^ swCP, int roundNum) {
	System::Console::WriteLine("PLAYER::WRITESCORETOFILE");
	int hasChips = (GetHasChips()) ? 1 : 0;
	System::String^ line = ("Round {0}\n\tName: {2}\n\tScore: {3}\n\tStill in : {4}\n", roundNum, GetPlayerName(), GetChipCount(), hasChips.ToString());
	swCP->WriteLine(line);
	

}

void Player::ReadInfoFromDirectoryFile(System::IO::StreamReader^ srCP) {
	System::Console::WriteLine("PLAYER::READINFOFROMDIRECTORYFILE");
	System::String^ line = "";
	System::String^ nameLine;
	System::String^ scoreLine;
	System::String^ hasChipsLine;

	System::Console::WriteLine(srCP->Peek());

	int count = 0;
	while (count < 3) {
		while (line != nullptr) {
			// read all lines from text
			line = srCP->ReadLine();
			System::Console::WriteLine(line);

			try {
				nameLine = line->Substring(0, 7);
				if (nameLine->CompareTo("\tName: ") == 0) {
					line = line->Substring(7);
					EnterPlayerName(line);
					System::Console::WriteLine(line);
					count++;
				}

			}
			catch (System::NullReferenceException^ e) {}
			catch (...) {}

			try {
				hasChipsLine = line->Substring(0, 11);
				if (hasChipsLine->CompareTo("\tStill in: ") == 0) {

					line = line->Substring(11);
					int zeroOrOne = int::Parse(line);
					//System::Console::WriteLine("1 for yes, 0 for no; {0}", line);
					if (zeroOrOne == 0) {
						EnterHasChips(false);
						System::Console::WriteLine(line);
						count++;
					}
					else {
						EnterHasChips(true);
						System::Console::WriteLine(line);
						count++;
					}
				}

			}
			catch (System::NullReferenceException^ e) {}
			catch (...) {
				System::Console::WriteLine("OMG, how did this get here!");
			}


			try {
				System::Console::WriteLine("Trying to read Score Line");
				scoreLine = line->Substring(0, 8);
				if (scoreLine->CompareTo("\tScore: ") == 0) {
					line = line->Substring(8);
					int chips = int::Parse(line);
					SetChipCount(chips);
					if (GetChipCount() < 1) {
						// player does not have chips, player cannot continue turn
						EnterHasChips(false);
					}
					System::Console::WriteLine(line);
					count++;
				}
			}
			catch (System::NullReferenceException^ e) {}
			catch (...) {
				System::Console::WriteLine("Woof you really don't want that!");
			}
		}
	}
}

void Player::ChangeScores(int diceRoll, int roundNum, System::IO::StreamReader^ srCP, System::IO::StreamReader^ srRP, System::IO::StreamReader^ srLP, System::IO::StreamWriter^ swCP, System::IO::StreamWriter^ swRP, System::IO::StreamWriter^ swLP) {
	System::Console::WriteLine("PLAYER::CHANGESCORES");
	int currentChips = GetChipCount();
	
	// rolled L
	if (diceRoll == 0) {
		System::Console::WriteLine("Changing Right Player Chips");
		ReadInfoFromDirectoryFile(srLP);
		SetChipCount(GetChipCount() + 1);
		WriteScoreToFile(swLP, roundNum);
		// take one chip from current player chip count
		System::Console::WriteLine("Changing Current Player Chips");
		ReadInfoFromDirectoryFile(srCP);
		currentChips--;
		WriteScoreToFile(swCP, roundNum);
		// print dice
		System::Console::WriteLine("You gave a chip to the left, ");
		System::Console::WriteLine("Chip Count now: {0}\n", GetChipCount());
	}
	// rolled R
	else if (diceRoll == 1) {
		ReadInfoFromDirectoryFile(srRP);
		SetChipCount(GetChipCount() + 1);
		WriteScoreToFile(swRP, roundNum);
		// take one chip from current player chip count
		ReadInfoFromDirectoryFile(srCP);
		currentChips--;
		WriteScoreToFile(swCP, roundNum);
		// print dice
		System::Console::WriteLine("You gave a chip to the right, ");
		System::Console::WriteLine("Chip Count now: {0}\n", GetChipCount());
	}
	// rolled C
	else if (diceRoll == 2) {
		// take one chip from current player chip count
		ReadInfoFromDirectoryFile(srCP);
		currentChips--;
		WriteScoreToFile(swCP, roundNum);
		// print dice
		System::Console::WriteLine("You gave a chip to the bank, ");
		System::Console::WriteLine("Chip Count now: {0}\n", GetChipCount());
	}
	// rolled * (no change to chip counts)
	else {
		// print dice
		System::Console::WriteLine("You still have {0} chips.\n", GetChipCount());
	}
}


