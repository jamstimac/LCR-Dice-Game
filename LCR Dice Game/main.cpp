// James Stimac, IT-312-J1214, 21-10-2022, final project LCR dice game
// 
// This program follows a clr/cli compilation, many of the problems that i had
// started from not understnad how to compile with clr. After I figured this out
// it was just a matter of time before the program practically wrote itself.
// 
// The game LRC like it's name "Left Right Center" is all about who is center
// or the current player, who is left of them and who is right of them. This name 
// also has a meaning for the dice. Simply, rolling an L moves one of your chips 
// to the left player. Rolling an R moves one of your chips to the right player, 
// and rolling a C moves one of your dice to the bank in the center.
// 
// The program follows standard set during this course, and was built with 
// a sense of Object Oriented Programing in mind. The source and header files 
// all follow industry standards and also encapsulate the functionality of the game
// to allow more direct udnerstanding of how the different portions need to interact.
// 
// When first writing the program a major issue I found (a little too late) came from
// creating a system that allowed for any number of players. I started by trying to build
// directories per round that help each players files; however, this began to break down when 
// it started to require 6 stream objects (3 stream writers and 3 stram readers). 
// 
// When this happened, my first thought was to try FileInfo, but that also didn't work.
// Eventually, I settled on a cli::array of Player objects that I could initialize in a 
// function and then never have to worry about. A major benefit of this form of array
// is that the initializtion allows for non constant int values. This solved most of
// the problems I faced and allowed me to focus more on building game functionality.
// 
// Thank you,
// James

#include "pch.h"
#include "Game.h"

using namespace System;

int main(array<System::String ^> ^args) {

    Game^ game = gcnew Game();

    game->Play();

    return 0;
}
