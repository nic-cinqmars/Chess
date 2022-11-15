#pragma once
#include <iostream>
#include <windows.h>
#include "BoardSpace.h"
#include "PawnPiece.h"
#include "RookPiece.h"
#include "KnightPiece.h"
#include "BishopPiece.h"
#include "QueenPiece.h"
#include "KingPiece.h"

class Board
{

public:
	static const int BOARD_SIZE = 8;

	Board();

	void printBoard();
	void checkPossibleMoves(int posX, int posY);
private:
	const int BOARD_DISPLAY_MAGNITUDE = 3; // Odd number only
	BoardSpace spaces[BOARD_SIZE][BOARD_SIZE];
};

