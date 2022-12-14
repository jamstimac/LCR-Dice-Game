#include "pch.h"
#include "Player.h"

Player::Player(System::String^ enteredName, int chips) {

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
	int rolls = (GetChipCount() > 3) ? 3 : GetChipCount();
	return rolls;
}

// takes array and adds player objects to array with starting info including Name, chipCount=3, and hasChips=true
void Player::WritePlayersToArray(array<Player^>^ pArray, Player^ player, int playerNum) {

	for (int i = 0; i < playerNum; i++) {
		System::Console::WriteLine("\nPlease enter player {0}'s name: ", (i + 1));
		System::String^ playerName = System::Console::ReadLine();
		Player^ thisPlayer = gcnew Player(playerName, STARTING_NUM_CHIPS_AND_PlAYERS);

		pArray[i] = thisPlayer;

		//System::Console::WriteLine("ChipCount: {0}\nName: {1}\nHasChips: {2}", pArray[i]->GetChipCount(), pArray[i]->GetPlayerName(), pArray[i]->GetHasChips());
	}
}


// gets current scores, uses diceRoll to set new scores
void Player::ChangeScores(int diceRoll, Player^ cPlayer, Player^ rPlayer, Player^ lPlayer) {
	//System::Console::WriteLine("PLAYER::CHANGESCORES");
	
	// rolled L
	if (diceRoll == 0) {
		// print what roll means
		System::Console::WriteLine("You rolled an 'L'. One of your chips goes to {0}", lPlayer->GetPlayerName());
		// add chip to Left Player chipCount
		lPlayer->AddChip();
		// remove chip from current player chipCount
		cPlayer->SubtractChip();
		
		// print current chip count
		System::Console::WriteLine("Current chip count: {0}\n", cPlayer->GetChipCount());
	}
	// rolled R
	else if (diceRoll == 1) {
		// print what roll means
		System::Console::WriteLine("You rolled an 'R'. One of your chips goes to {0}", rPlayer->GetPlayerName());
		// add chip to Right Player chipCount
		rPlayer->AddChip();
		// remove chip from current player chipCount
		cPlayer->SubtractChip();

		// print current chip count
		System::Console::WriteLine("Current chip count: {0}", cPlayer->GetChipCount());
	}
	// rolled C
	else if (diceRoll == 2) {
		// 
		System::Console::Write("You rolled a 'C'. ");
		// remove chip from current player chipCount
		cPlayer->SubtractChip();
		
		System::Console::WriteLine("You gave a chip to the bank, ");
		System::Console::WriteLine("chip Count now: {0}\n", cPlayer->GetChipCount());
	}
	// rolled *
	else {
		// no exchange of chips
		System::Console::WriteLine("You rolled an '*', ");
		System::Console::WriteLine("You still have {0} chips.\n", cPlayer->GetChipCount());
	}
	
}

// runs through player array, returns 1 if one 1 player has chips, 0 to continue play.
int Player::ReturnEndLoop(cli::array<Player^>^ pArray, int playerNum) {
	int countHowManyPlayersHaveChips = 0;

	// run through array of players set hasChips, set int count...;
	for (int i = 0; i < playerNum; i++) {
		// sets bool
		pArray[i]->SetHasChips();
		// checks bool adds to count
		if (pArray[i]->GetHasChips()) {
			countHowManyPlayersHaveChips++;
		}
	}

	// if only one player has chips
	if (countHowManyPlayersHaveChips <= 1) {
		return 1;
	}
	else {
		return 0;
	}
}

// takes scores and winner and writes them to save file (functionality can be added later to retrieve save information)
void Player::WriteScoreToFile(int roundNum) {
	System::Console::WriteLine("Scores saved to file {0}", FINAL_SCORE_FILE_NAME);
	System::IO::StreamWriter^ swWinner = gcnew System::IO::StreamWriter(FINAL_SCORE_FILE_NAME);

	swWinner->WriteLine("Nice going Name: {0}! You won LRC!", GetPlayerName());
	swWinner->WriteLine("");
	swWinner->WriteLine("You playerd {0} round(s)", roundNum);
	swWinner->WriteLine("Your final score was {0}", GetChipCount());
	swWinner->WriteLine("");
	swWinner->WriteLine(CREDITS);
	

	swWinner->Close();

}

// runs through the array and returns the Player obj that has chips
Player^ Player::ReturnWinner(cli::array<Player^>^ pArray, int numPlayers) {
	Player^ winner;

	for (int i = 0; i < numPlayers; i++) {
		// if player with index i has chips
		// store their name in NameOfWinner
		if (pArray[i]->GetHasChips()) {
			winner = pArray[i];
		}
	}

	return winner;
}