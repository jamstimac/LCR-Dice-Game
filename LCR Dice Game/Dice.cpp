#include "pch.h"
#include "Dice.h"

Dice::Dice() {
	srand(time(NULL));
	System::Console::WriteLine("DICE::.CTOR");
};

int Dice::Roll() {
	return (rand() % NUM_SIDES);
}

