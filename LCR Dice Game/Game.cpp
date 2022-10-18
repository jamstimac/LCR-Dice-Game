#include "pch.h"
#include "Game.h"

Game::Game() {
	System::Console::WriteLine("Game::.CTOR");
};

void Game::Play() {
	System::Console::WriteLine("Instance: Game::Play()");
	
    Dice^ dice = gcnew Dice();

    System::Console::WriteLine("Hello.");

    int diceRoll1, diceRoll2;
    diceRoll1 = dice->Roll();
    diceRoll2 = dice->Roll();

    System::Console::WriteLine("First roll: {0} Second roll: {1}", diceRoll1, diceRoll2);
    System::String^ name = "Jerry";

    Player^ player = gcnew Player();

	WelcomePlayer();

}

void Game::WelcomePlayer(System::String^ introFile) {
	/// <summary>
	/// Welcomes the player to the game
	/// reads intro paragraphs from .txt file
	/// 
	/// pulls function design from 
	/// https://learn.microsoft.com/en-us/cpp/dotnet/file-handling-and-i-o-cpp-cli?view=msvc-170&viewFallbackFrom=vs-2017#read_text
	/// </summary>

	System::String^ fileName = "GameIntro.txt";
	try
	{
		System::IO::StreamReader^ strmrd = System::IO::File::OpenText(fileName);

		System::String^ str;
		int count = 0;
		while ((str = strmrd->ReadLine()) != nullptr)
		{
			count++;
			System::Console::WriteLine(str);
		}
	}
	catch (System::Exception^ e)
	{
		if (dynamic_cast<System::IO::FileNotFoundException^>(e))
			System::Console::WriteLine("file '{0}' not found", fileName);
		else
			System::Console::WriteLine("problem reading file '{0}'", fileName);
	}

}



