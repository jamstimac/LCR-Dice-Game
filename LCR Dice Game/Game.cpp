#include "pch.h"
#include "Game.h"

Game::Game() {
	//System::Console::WriteLine("Game::.CTOR");
};

void Game::Play() {
	// constructor seeds srand()
	Dice^ dice = gcnew Dice();
	Player^ player = gcnew Player();

	// function variables
	System::String^ introFile = "GameIntro.txt";
	System::String^ scoresFile = "Scores.txt";
	unsigned int roundNum = 0;

	// welcome player get numPlayers
	WelcomePlayer(introFile);
	numPlayers = GetNumPlayers();

	
	// get names of each player and initialize each player into a save file
	player->WritePlayersToFile(scoresFile, roundNum, numPlayers);

	roundNum = 1;
	player->EditFileUpdatedScores(scoresFile, roundNum);
	/*do {
		


	} while (endLoop == 0);*/
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
		System::IO::StreamReader^ streamReader= System::IO::File::OpenText(fileName);

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


