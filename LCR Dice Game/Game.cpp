#include "pch.h"
#include "Game.h"

Game::Game() {
	
};

// initializes dice, player and playerArray objects, gets numPlayers, defines array with numPlayer,
// continues game
void Game::Play() {
	// constructor seeds fiand()
	Dice^ dice = gcnew Dice();
	Player^ player = gcnew Player("", 3);

	cli::array<Player^>^ playerArray;

	// function variables
	int endLoop = 0;

	// welcome player get numPlayers
	WelcomePlayer();
	numPlayers = GetNumPlayers();
	playerArray = gcnew cli::array<Player^>(numPlayers);

	player->WritePlayersToArray(playerArray, player, numPlayers);

	System::Console::WriteLine();

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
			int currentPlayer = (i + 1);
			System::Console::WriteLine("\nPlayer {0}", currentPlayer);

			GetRightLeftAndCurrentPlayer(dice, player, playerArray, roundNum, currentPlayer, numPlayers);
			


			// allows user a second to read results
			// press enter to continue
			PauseTurn();			
		}
		// check for winner
		endLoop = 1;
	} while (endLoop == 0);
}

// Initializes numPlayers, then runs a do loop to get a number of players
int Game::GetNumPlayers() {

	System::Console::WriteLine("GAME::GETNUMPLAYERS");
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
		catch (System::FormatException^) {
			System::Console::WriteLine("Please enter a number 3 or more.");
		}
		
	} while (numPlayers < STARTING_NUM_CHIPS_AND_PlAYERS);

	return numPlayers;
}
//
// takes player array returns indexes for current left and right player
// passes dice and player and array objects to following functions
void Game::GetRightLeftAndCurrentPlayer(Dice^ dice, Player^ player, cli::array<Player^>^ pArray, int roundNum, int currentPlayerNum, int numPlayers) {

	// example::						      // if 3 players, numbers become:
	System::Console::WriteLine("GAME::GETRIGHTLEFTANDCURRENTPLAYER");
	int currentPlayer = (currentPlayerNum);   // 1, 2, 3
	System::Console::WriteLine("CurrentPlayer: {0}", currentPlayer);
	int leftPlayer = (currentPlayerNum - 1);  // 3, 1, 2
	if (leftPlayer == 0) {
		leftPlayer = numPlayers;
	}
	System::Console::WriteLine("LeftPlayer: {0}", leftPlayer);
	int rightPlayer = (currentPlayerNum + 1); // 2, 3, 1
	if (rightPlayer > numPlayers) {
		rightPlayer = 1;
	}
	System::Console::WriteLine("RightPlayer: {0}", rightPlayer);

	CheckChipsRollUpdateScores(dice, player, pArray, currentPlayer, rightPlayer, leftPlayer);

}

void Game::CheckChipsRollUpdateScores(Dice^ dice, Player^ player, cli::array<Player^>^ pArray, int cpNum, int rpNum, int lpNum) {
	
	System::Console::WriteLine("GAME::CHECKCHIPSROLLUPDATESCORES");

	int diceRoll = 0;
	if (pArray[cpNum]->GetHasChips()) {
		int rollsCurrentPlayer = pArray[cpNum]->ReturnNumRolls();
		System::Console::WriteLine("\nWelcome {0} You have {1} chips.", pArray[cpNum]->GetPlayerName(), rollsCurrentPlayer);

		for (int i = 0; i < rollsCurrentPlayer; i++) {
			System::Console::WriteLine("Roll {0}", (i + 1));
			diceRoll = dice->Roll();
			dice->PrintSide(diceRoll);

			//player->ChangeScores(diceRoll, pArray, cpNum, rpNum, rpNum);

			PauseTurn();
		}
		System::Console::WriteLine("\nTime for the next player to roll.");
	}
	else {
		// pass turn
		System::Console::WriteLine();
		System::Console::WriteLine("You currently don't have chips! Keep at it, if you get chips this next round you can play again!");
		System::Console::WriteLine("Passing dice to next player\n");
		return;
	}



}



// reads welcome info from file GameIntro.txt
void Game::WelcomePlayer() {
	/// <summary>
	/// Welcomes the player to the game
	/// reads intro paragraphs from .txt file
	/// 
	/// pulls function design from 
	/// https://learn.microsoft.com/en-us/cpp/dotnet/file-handling-and-i-o-cpp-cli?view=msvc-170&viewFallbackFrom=vs-2017#read_text
	/// </summary>
	System::Console::WriteLine("GAME::WELCOMEPLAYER");

	try
	{
		System::IO::FileInfo^ fi = gcnew System::IO::FileInfo(INTRO_FILE_NAME);

		System::String^ str;
		str = fi->OpenText()->ReadToEnd();

		System::Console::WriteLine(str);
		System::Console::WriteLine();
	}
	catch (System::Exception^ e)
	{
		if (dynamic_cast<System::IO::FileNotFoundException^>(e))
			System::Console::WriteLine("file '{0}' not found", INTRO_FILE_NAME);
		else
			System::Console::WriteLine("problem reading file '{0}'", INTRO_FILE_NAME);
	}

}

// allows quick use of ReadLine() to pause turn, gives sense of control over dice rolls
void Game::PauseTurn() {
	System::Console::WriteLine("\nPress [enter] to continue!");
	System::Console::ReadLine();
}
