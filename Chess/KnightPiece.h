#pragma once
#include "Piece.h"

class KnightPiece : public Piece
{
public:
	KnightPiece(int color, std::vector<int> position);
	Piece* clone();
	std::vector<std::vector<int>> getMoves(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], bool includeMoveOnKing = false);
};

