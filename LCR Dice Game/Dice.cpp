#include "pch.h"
#include "Dice.h"

Dice::Dice() {
	srand(time(NULL));
	System::Console::WriteLine("DICE::.CTOR");
};

int Dice::Roll() {
	return (rand() % NUM_SIDES);
}

void PrintSide(int diceRoll, char diceArray[]) {
	// print dice
	System::Console::WriteLine(" --- ");
	System::Console::WriteLine("| {0} |", diceArray[diceRoll]);
	System::Console::WriteLine(" --- ");
}