#include "pch.h"
#include "Game.h"

Game::Game() {

};

void Game::Play() {
	// constructor seeds srand()
	Dice^ dice = gcnew Dice();
	Player^ player = gcnew Player("", 3);

	// creates directory that will hold all player info
	System::IO::DirectoryInfo^ di = gcnew System::IO::DirectoryInfo(DIRECTORY_NAME);
	di->Create();


	// function variables
	System::String^ introFile = "GameIntro.txt";
	int endLoop = 0;


	

	// welcome player get numPlayers
	WelcomePlayer(introFile);
	numPlayers = GetNumPlayers();

	

	
	// get names of each player and initialize each player into a save file
	// directory allows access to each players file individually
	// directory file names are based on numPlayer (for loop int i + 1) per player
	player->WriteFilesToPlayerDirectory(di, numPlayers, roundNum);
	

	// game loop
	//		currentPlayer = for loop i num
	//		Checks chips (print current chips)
	//		Rolls dice (print dice based on chip num)
	//		Exchanges chips (0-2 current player looses chips)
	//		check for winner (
	//		
	do {
		// begin new round
		roundNum++;
		// game for loop
		for (int i = 0; i < numPlayers; i++) {
			System::String^ currentPlayer = (i + 1).ToString();
			System::Console::WriteLine("Player {0}", currentPlayer);

			GetRightLeftAndCurrentPlayer(di, dice, player, i, numPlayers);
			
		}
		// check for winner
		endLoop = 1;
	} while (endLoop == 0);
}


void Game::WelcomePlayer(System::String^ fileName) {
	/// <summary>
	/// Welcomes the player to the game
	/// reads intro paragraphs from .txt file
	/// 
	/// pulls function design from 
	/// https://learn.microsoft.com/en-us/cpp/dotnet/file-handling-and-i-o-cpp-cli?view=msvc-170&viewFallbackFrom=vs-2017#read_text
	/// </summary>

	try
	{
		System::IO::StreamReader^ streamReader = System::IO::File::OpenText(fileName);

		System::String^ str;
		int count = 0;
		while ((str = streamReader->ReadLine()) != nullptr)
		{
			count++;
			System::Console::WriteLine(str);
		}

		System::Console::WriteLine();
	}
	catch (System::Exception^ e)
	{
		if (dynamic_cast<System::IO::FileNotFoundException^>(e))
			System::Console::WriteLine("file '{0}' not found", fileName);
		else
			System::Console::WriteLine("problem reading file '{0}'", fileName);
	}

}


int Game::GetNumPlayers() {
	/// <summary>
	/// Initializes numPlayers, then runs a do loop to get a number of players
	/// above 3. Catches both out of bounds exceptions and others.
	/// </summary>
	numPlayers = 0;

	System::Console::WriteLine("How many people are playing?");
	do {
		userInput = System::Console::ReadLine();
		try {
			numPlayers = int::Parse(userInput);
			if (numPlayers < 3) {
				System::Console::WriteLine("You must have at least 3 players.");
			}
		}
		catch (System::FormatException^ e) {
			System::Console::WriteLine("Please enter a number 3 or more.");
		}
		
	} while (numPlayers < STARTING_NUM_CHIPS_AND_PlAYERS);

	return numPlayers;
}


void Game::GetRightLeftAndCurrentPlayer(System::IO::DirectoryInfo^ di, Dice^ dice, Player^ player, int currentPlayerNum, int numPlayers) {
	/// <summary>
	///
	/// </summary>
	/// <param name="di"></param>
	/// <param name="currentPlayerNum"></param>
	///										   // if 3 players numbers become 
	int currentPlayer = (currentPlayerNum + 1);// 1, 2, 3

	int leftPlayer = (currentPlayerNum); // 3, 1, 2
	if (leftPlayer == 0) {
		leftPlayer = numPlayers;
	}

	int rightPlayer = (currentPlayerNum + 2); // 2, 3, 1
	if (rightPlayer > numPlayers) {
		rightPlayer = 1;
	}


	// current player's file
	System::String^ fileNameCP = ("{0}.txt", (DIRECTORY_NAME+PATH_TOKEN+currentPlayer.ToString()));
	// right player's file
	System::String^ fileNameRP = ("{0}.txt", (DIRECTORY_NAME+PATH_TOKEN+rightPlayer.ToString()));
	// left players's file
	System::String^ fileNameLP = ("{0}.txt", (DIRECTORY_NAME+PATH_TOKEN+leftPlayer.ToString()));

	System::IO::StreamReader^ srCurrentPlayer = gcnew System::IO::StreamReader(fileNameCP);
	System::IO::StreamReader^ srRightPlayer = gcnew System::IO::StreamReader(fileNameRP);
	System::IO::StreamReader^ srLeftPlayer = gcnew System::IO::StreamReader(fileNameLP);

	CheckChipsRollUpdateScores(dice, player, srCurrentPlayer, srRightPlayer, srLeftPlayer);

}

void Game::CheckChipsRollUpdateScores(Dice^ dice, Player^ player, System::IO::StreamReader^ srCP, System::IO::StreamReader^ srRP, System::IO::StreamReader^ srLP) {
	
	int rollsCurrentPlayer = GetChipCountReturnRolls(srCP, player);
	System::Console::WriteLine(player->GetPlayerName());
	System::Console::WriteLine("num rolls {0}", rollsCurrentPlayer.ToString());
	int diceRoll = 0;
	bool canRoll = (rollsCurrentPlayer > 0);
	if (canRoll) {
		for (int i = 0; i < rollsCurrentPlayer; i++) {
			diceRoll = dice->Roll();
			System::Console::WriteLine("diceroll: {0}", diceRoll.ToString());
			
		}

	}
	else {
		// pass turn
		System::Console::WriteLine();
		System::Console::WriteLine("You currently don't have chips! Keep at it, if you get chips this next round you can play again!");
		System::Console::WriteLine("Passing dice to next player");
		return;
	}



}

int Game::GetChipCountReturnRolls(System::IO::StreamReader^ srAffectedPlayer, Player^ player) {
	/// <summary> 
	/// reads from file info on current player enters their info into Player class
	/// returns num rolls based on chip count
	/// 
	/// also sets player class with current player info, necessary for later.
	///<\summary>
	System::String^ line;
	int rolls = 0;
	System::String^ nameLine;
	System::String^ scoreLine;
	System::String^ hasChipsLine;

	while ((line = srAffectedPlayer->ReadLine()) != nullptr) {
		
		try {
			//System::Console::WriteLine("atempting to read player name");
			nameLine = line->Substring(0, 7);
			if (nameLine->CompareTo("\tName: ") == 0) {
				line = line->Substring(7);
				player->EnterPlayerName(line);
				//System::Console::WriteLine("Name: {0}", line);
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
					player->EnterHasChips(false);
				}
				else {
					player->EnterHasChips(true);
				}
				System::Console::WriteLine(line);
			}
		}
		catch (System::NullReferenceException^ e) {}
		catch (...) {}


		try {
			//System::Console::WriteLine("atempting to read player score");
			scoreLine = line->Substring(0, 8);
			if (scoreLine->CompareTo("\tScore: ") == 0) {
				line = line->Substring(8);
				int chips = int::Parse(line);
				player->SetChipCount(chips);
				//System::Console::WriteLine("Current Score: {0}", line);
				if (player->GetChipCount() < 1) {
					// player does not have chips, player cannot continue turn
					player->EnterHasChips(false);

					rolls = 0;
					return rolls;
				}
			}
		}
		catch (System::NullReferenceException^ e) {}
		catch (...) {}

		rolls = (player->GetChipCount() > 3) ? 3 : player->GetChipCount();
	}
	return rolls;

}
