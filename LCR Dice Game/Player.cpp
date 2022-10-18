#include "pch.h"
#include "Player.h"

Player::Player() {
	System::Console::WriteLine("PLAYER::.CTOR");
	
	System::Console::WriteLine("Enter your name: ");
	name = System::Console::ReadLine();
	chipCount = 3;
	hasChips = true;
	
	System::Console::WriteLine("Name: {0}\nChipCount: {1}\nHasChips {2}", name, chipCount, hasChips);
}


