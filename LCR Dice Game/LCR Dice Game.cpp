#include "pch.h"

using namespace System;

int main(array<System::String ^> ^args) {
    Game^ game = gcnew Game();

    game->Play();

    return 0;
}

/*
* 
TODO:
Copy simple Game.h with only the constructor and check that it builds.
Copy Play declaration and definition, but *only* with the writeline function, to make sure it builds.
Slowly add lines of implementation until you need the other classes, then add each class to the .net project through the wizard in turn.
If you add something and it breaks, comment out lines you added until it builds, then re-add them one at a time to check yourself.

*/