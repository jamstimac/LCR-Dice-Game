#include "pch.h"
#include "Game.h"

Game::Game() {
	
};

void Game::Play() {
	// constructor seeds fiand()
	Dice^ dice = gcnew Dice();
	Player^ player = gcnew Player("", 3);

	// creates directory that will hold all player info
	System::IO::DirectoryInfo^ di = gcnew System::IO::DirectoryInfo(DIRECTORY_NAME);
	di->Create();

	// function variables
	int endLoop = 0;

	// welcome player get numPlayers
	WelcomePlayer();
	numPlayers = GetNumPlayers();

	// get names of each player and initialize each player into a save file
	// directory allows access to each players file individually
	// directory file names are based on numPlayer (for loop int i + 1) per player
	System::String^ subDirectoryStr = ROUND + (roundNum.ToString());
	di->CreateSubdirectory(subDirectoryStr);
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
		subDirectoryStr = ROUND + (roundNum.ToString());
		di->CreateSubdirectory(subDirectoryStr);
		// game for loop
		for (int i = 0; i < numPlayers; i++) {
			System::String^ currentPlayer = (i + 1).ToString();
			System::Console::WriteLine("\nPlayer {0}", currentPlayer);

			GetRightLeftAndCurrentPlayer(dice, player, roundNum, i, numPlayers);
			


			// allows user a second to read results
			// press enter to continue
			PauseTurn();			
		}
		// check for winner
		endLoop = 1;
	} while (endLoop == 0);
}



void Game::WelcomePlayer() {
	/// <summary>
	/// Welcomes the player to the game
	/// reads intro paragraphs from .txt file
	/// 
	/// pulls function design from 
	/// https://learn.microsoft.com/en-us/cpp/dotnet/file-handling-and-i-o-cpp-cli?view=msvc-170&viewFallbackFrom=vs-2017#read_text
	/// </summary>
	System::Console::WriteLine("GAME::WELCOMEPLAYER");

	System::String^ introFile = "GameIntro.txt";
	 
	try
	{
		System::IO::FileInfo^ fi = gcnew System::IO::FileInfo(introFile);

		System::String^ str;
		str = fi->OpenText()->ReadToEnd();

		System::Console::WriteLine(str);
		System::Console::WriteLine();
	}
	catch (System::Exception^ e)
	{
		if (dynamic_cast<System::IO::FileNotFoundException^>(e))
			System::Console::WriteLine("file '{0}' not found", introFile);
		else
			System::Console::WriteLine("problem reading file '{0}'", introFile);
	}
	
}

void Game::PauseTurn() {
	System::Console::WriteLine("\nPress [enter] to continue!");
	System::Console::ReadLine();
}

int Game::GetNumPlayers() {
	/// <summary>
	/// Initializes numPlayers, then runs a do loop to get a number of players
	/// above 3. Catches both out of bounds exceptions and others.
	/// </summary>
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
		catch (System::FormatException^ e) {
			System::Console::WriteLine("Please enter a number 3 or more.");
		}
		
	} while (numPlayers < STARTING_NUM_CHIPS_AND_PlAYERS);

	return numPlayers;
}


void Game::GetRightLeftAndCurrentPlayer(Dice^ dice, Player^ player, int roundNum, int currentPlayerNum, int numPlayers) {
	/// <summary>
	///
	/// </summary>
	/// <param name="di"></param>
	/// <param name="currentPlayerNum"></param>
	///										   // if 3 players numbers become 
	System::Console::WriteLine("GAME::GETRIGHTLEFTANDCURRENTPLAYER");
	int currentPlayer = (currentPlayerNum + 1);// 1, 2, 3

	int leftPlayer = (currentPlayerNum); // 3, 1, 2
	if (leftPlayer == 0) {
		leftPlayer = numPlayers;
	}

	int rightPlayer = (currentPlayerNum + 2); // 2, 3, 1
	if (rightPlayer > numPlayers) {
		rightPlayer = 1;
	}
	//round num has to be prior to return past scores/names
	System::String^ roundFolderDir = DIRECTORY_NAME + PATH_TOKEN + ROUND + ((roundNum-1).ToString()) + PATH_TOKEN;

	// current player's file
	System::String^ fileNameCP = ("{0}.txt", (roundFolderDir + currentPlayer.ToString()));
	// right player's file
	System::String^ fileNameRP = ("{0}.txt", (roundFolderDir + rightPlayer.ToString()));
	// left players's file
	System::String^ fileNameLP = ("{0}.txt", (roundFolderDir + leftPlayer.ToString()));

	System::IO::FileInfo^ fiCurrentPlayer = gcnew System::IO::FileInfo(fileNameCP);
	System::IO::FileInfo^ fiRightPlayer = gcnew System::IO::FileInfo(fileNameRP);
	System::IO::FileInfo^ fiLeftPlayer = gcnew System::IO::FileInfo(fileNameLP);

	CheckChipsRollUpdateScores(roundNum, dice, player, fiCurrentPlayer, fiRightPlayer, fiLeftPlayer);

}

void Game::CheckChipsRollUpdateScores(int roundNum, Dice^ dice, Player^ player, System::IO::FileInfo^ fiCP, System::IO::FileInfo^ fiRP, System::IO::FileInfo^ fiLP) {
	
	System::Console::WriteLine("GAME::CHECKCHIPSROLLUPDATESCORES");

	/// <summary>
	/// 
	/// </summary>
	/// <param name="dice"></param>
	/// <param name="player"></param>
	/// <param name="srCP"></param>
	/// <param name="srRP"></param>
	/// <param name="srLP"></param>
	
	// GetChipCountReturnRolls not working... can't find file in directory
	int rollsCurrentPlayer = GetChipCountReturnRolls(fiCP, player);
	int diceRoll = 0;
	bool canRoll = (rollsCurrentPlayer > 0);

	System::Console::WriteLine("\nWelcome{0} You have{1} chips.", player->GetPlayerName(), rollsCurrentPlayer.ToString());
	
	if (canRoll) {
		for (int i = 0; i < rollsCurrentPlayer; i++) {
			System::Console::WriteLine("Roll {0}", (i + 1));
			diceRoll = dice->Roll();
			dice->PrintSide(diceRoll);
			
			player->ChangeScores(diceRoll, roundNum, fiCP, fiRP,fiLP);
			
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

int Game::GetChipCountReturnRolls(System::IO::FileInfo^ fiAffectedPlayer, Player^ player) {
	/// <summary> 
	/// reads from file info on current player enters their info into Player class
	/// returns num rolls based on chip count
	/// 
	/// also sets player class with current player info, necessary for later.
	///<\summary>
	System::Console::WriteLine("GAME::GETCHIPCOUNTRETURNROLLS");
	int rolls = 0;

	player->ReadInfoFromDirectoryFile(fiAffectedPlayer);

	rolls = (player->GetChipCount() > 3) ? 3 : player->GetChipCount();
	return rolls;

}
