#pragma once
#include "Piece.h"

class QueenPiece : public Piece
{
public:
	QueenPiece(int color, std::vector<int> position);
	std::vector<std::vector<int>> getMoves(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE]);
};

