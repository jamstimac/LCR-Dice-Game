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

void Player::WriteScoreToFile(System::IO::FileInfo^ fiCP, int roundNum) {
	System::Console::WriteLine("PLAYER::WRITESCORETOFILE");
	int hasChips = (GetHasChips()) ? 1 : 0;
	System::String^ line = ("Round {0}\n\tName: {2}\n\tScore: {3}\n\tStill in : {4}\n", roundNum, GetPlayerName(), GetChipCount(), hasChips.ToString());
	fiCP->CreateText()->WriteLine(line);
	

}

void Player::ReadInfoFromDirectoryFile(System::IO::FileInfo^ fiThisPlayer) {
	System::Console::WriteLine("PLAYER::READINFOFROMDIRECTORYFILE");
	System::String^ line;
	System::String^ nameLine;
	System::String^ scoreLine;
	System::String^ hasChipsLine;
	
	int count = 0;
	while (count < 3) {
		line = fiThisPlayer->OpenText()->ReadToEnd();
		// can you split line at \n?
		System::Console::Write("Loop iteration");
		try {
			//System::Console::WriteLine("atempting to read player name");
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
			//System::Console::WriteLine("atempting to read player chipCount");
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
		catch (...) {}


		try {

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
		catch (...) {}
	}
	System::Console::Write("end while Loop iteration");
}

void Player::ChangeScores(int diceRoll, int roundNum, System::IO::FileInfo^ fiCP, System::IO::FileInfo^ fiRP, System::IO::FileInfo^ fiLP) {
	System::Console::WriteLine("PLAYER::CHANGESCORES");
	int currentChips = GetChipCount();

	// rolled L
	if (diceRoll == 0) {
		ReadInfoFromDirectoryFile(fiLP);
		SetChipCount(GetChipCount() + 1);
		WriteScoreToFile(fiLP, roundNum);
		// take one chip from current player chip count
		ReadInfoFromDirectoryFile(fiCP);
		currentChips--;
		WriteScoreToFile(fiLP, roundNum);
		// print dice
		System::Console::WriteLine("You gave a chip to the left, ");
		System::Console::WriteLine("Chip Count now: {0}\n", this->GetChipCount());
	}
	// rolled R
	else if (diceRoll == 1) {
		ReadInfoFromDirectoryFile(fiRP);
		SetChipCount(GetChipCount() + 1);
		WriteScoreToFile(fiRP, roundNum);
		// take one chip from current player chip count
		ReadInfoFromDirectoryFile(fiCP);
		currentChips--;
		WriteScoreToFile(fiCP, roundNum);
		// print dice
		System::Console::WriteLine("You gave a chip to the right, ");
		System::Console::WriteLine("Chip Count now: {0}\n", this->GetChipCount());
	}
	// rolled C
	else if (diceRoll == 2) {
		// take one chip from current player chip count
		ReadInfoFromDirectoryFile(fiCP);
		currentChips--;
		WriteScoreToFile(fiCP, roundNum);
		// print dice
		System::Console::WriteLine("You gave a chip to the bank, ");
		System::Console::WriteLine("Chip Count now: {0}\n", this->GetChipCount());
	}
	// rolled * (no change to chip counts)
	else {
		// print dice
		System::Console::WriteLine("You still have {0} chips.\n", this->GetChipCount());
	}
	
}


