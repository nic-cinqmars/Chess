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
	bool attemptPieceMove(std::vector<int> pieceToMove, int player, std::vector<int> destination);
	void movePiece(std::vector<int> originalPosition, std::vector<int> newPosition);

private:
	const int BOARD_DISPLAY_MAGNITUDE = 3; // Odd number only
	BoardSpace spaces[BOARD_SIZE][BOARD_SIZE];
};

