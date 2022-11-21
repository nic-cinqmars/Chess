#pragma once
#include <vector>
#include "Movement.h"
#include "BoardSpace.h"
#include "Globals.h"

class Piece
{
protected:
	int color;
	bool empty = false;
	char displayedChar;
	std::vector<int> position;

public:
	virtual std::vector<std::vector<int>> getMoves(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE]) = 0;
	virtual void move(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], std::vector<int> destination);
	int getColor();
	char getDisplayedChar();
	std::vector<int> getPosition();
};

