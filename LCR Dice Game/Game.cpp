#include "pch.h"
#include "Game.h"

Game::Game() {
	System::Console::WriteLine();
};

// initializes dice, player and playerArray objects, gets numPlayers, defines array with numPlayer,
// continues game
void Game::Play() {
	// constructor seeds srand()
	Dice^ dice = gcnew Dice();
	Player^ player = gcnew Player("", 3);
	Player^ winner = gcnew Player("", 0);

	cli::array<Player^>^ playerArray;

	// function variables
	int endLoop = 0;

	// welcome player get numPlayers
	WelcomePlayer();
	numPlayers = GetNumPlayers();
	playerArray = gcnew cli::array<Player^>(numPlayers);

	player->WritePlayersToArray(playerArray, player, numPlayers);

	// game loop
	//		currentPlayer = for loop i num
	//		Checks chips (print current chips)
	//		Rolls dice (print dice based on chip num)
	//		Exchanges chips (0-2 current player looses chips)
	//		check for winner (
	//		
	do {
		// allows user a second to read results
		// press enter to continue
		PauseTurn();
		// begin new round
		roundNum++;
		// game for loop
		for (int i = 0; i < numPlayers; i++) {
			// i stands for current player num
			// gets current players, checks chips, rolls, updates scores
			GetRightLeftAndCurrentPlayer(dice, player, playerArray, i, numPlayers);

			// check scores
			endLoop = player->ReturnEndLoop(playerArray, numPlayers);

			// set winner num breaks loop when found
			if (endLoop != 0) {
				winner = player->ReturnWinner(playerArray, numPlayers);
				break;
			}
		}
	} while (endLoop == 0);

	System::Console::WriteLine("Congrats {0}, you are the winner!", winner->GetPlayerName());

	winner->WriteScoreToFile(roundNum);
}

// Initializes numPlayers, then runs a do loop to get a number of players
int Game::GetNumPlayers() {

	//System::Console::WriteLine("GAME::GETNUMPLAYERS");
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
void Game::GetRightLeftAndCurrentPlayer(Dice^ dice, Player^ player, cli::array<Player^>^ pArray, int currentPlayerNum, int numPlayers) {

	// finds indexes for players affected this set of rolls
	// example::						      // if 3 players, numbers become:
	System::Console::WriteLine("Getting current players...");
	int currentPlayer = (currentPlayerNum);   // 0, 1, 2
	//System::Console::WriteLine("CurrentPlayer: {0}", currentPlayer);
	int leftPlayer = (currentPlayerNum - 1);  // 2, 0, 1
	if (leftPlayer < 0) {
		leftPlayer = (numPlayers -1);
	}
	//System::Console::WriteLine("LeftPlayer: {0}", leftPlayer);
	int rightPlayer = (currentPlayerNum + 1); // 1, 2, 0
	if (rightPlayer == numPlayers) {
		rightPlayer = 1;
	}
	//System::Console::WriteLine("RightPlayer: {0}", rightPlayer);

	// initialize players based on indexes found above
	Player^ currentPlayerObj = pArray[currentPlayer];
	Player^ rightPlayerObj = pArray[rightPlayer];
	Player^ leftPlayerObj = pArray[leftPlayer];
	//System::Console::WriteLine("Names: 1::{0} 2::{1} 3::{2}", currentPlayerObj->GetPlayerName(), rightPlayerObj->GetPlayerName(), leftPlayerObj->GetPlayerName());
	
	CheckChipsRollUpdateScores(dice, player, currentPlayerObj, rightPlayerObj, leftPlayerObj);

	// return and check endLoop int;
}

void Game::CheckChipsRollUpdateScores(Dice^ dice, Player^ player, Player^ cPlayer, Player^ rPlayer, Player^ lPlayer) {
	
	//System::Console::WriteLine("GAME::CHECKCHIPSROLLUPDATESCORES");

	int diceRoll = 0;
	if (cPlayer->GetHasChips()) {
		int rollsCurrentPlayer = cPlayer->ReturnNumRolls();
		System::Console::WriteLine("\nWelcome {0} You have {1} chips so you may roll {2} time(s)", cPlayer->GetPlayerName(), cPlayer->GetChipCount(), rollsCurrentPlayer);
		
		PauseTurn();

		for (int i = 0; i < rollsCurrentPlayer; i++) {
			System::Console::WriteLine("Roll {0}", (i + 1));
			diceRoll = dice->Roll();
			dice->PrintSide(diceRoll);

			player->ChangeScores(diceRoll, cPlayer, rPlayer, lPlayer);

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
	//System::Console::WriteLine("GAME::WELCOMEPLAYER");

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
	System::Console::WriteLine("\nPress [enter] to continue!\n");
	System::Console::ReadLine();
}
