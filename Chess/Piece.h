#pragma once
#include "Movement.h"

class Piece
{
protected:
	int color;
	bool empty = false;
	char displayedChar;

public:
	virtual Movement move() = 0;
	int getColor();
	bool isEmpty();
	char getDisplayedChar();
};

