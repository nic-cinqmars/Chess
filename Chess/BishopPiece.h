#pragma once
#include "Piece.h"

class BishopPiece : public Piece
{
public:
	BishopPiece(int color, std::vector<int> position);
	Piece* clone();
	std::vector<std::vector<int>> getMoves(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], bool includeMoveOnKing = false);
};

