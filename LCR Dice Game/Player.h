#pragma once

#include "pch.h"

ref class Player {
public:
	Player();

private:
	System::String^ name;
	unsigned int chipCount;
	bool hasChips;
};

