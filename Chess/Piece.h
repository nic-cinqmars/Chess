#pragma once
class Piece
{
protected:
	int color;
	bool empty = false;
	char displayedChar;

public:
	virtual void move() = 0;
	int getColor();
	bool isEmpty();
	char getDisplayedChar();
};

