#include "pch.h"
#include "Dice.h"
#include <cstdlib>
#include <string>

Dice::Dice() {
	srand(time(NULL));
	System::Console::WriteLine("Get ready to roll some dice!\n");
};

int Dice::Roll() {
	return (rand() % NUM_SIDES);
}

void Dice::PrintSide(int diceRoll) {
	// print dice
	std::string diceArray[NUM_SIDES] = { "L", "R", "C", "*",  "*", "*" };

	System::String^ sideString = gcnew System::String(diceArray[diceRoll].c_str());

	System::Console::WriteLine("\t --- ");
	System::Console::WriteLine("\t| {0} |", sideString);
	System::Console::WriteLine("\t --- ");
}