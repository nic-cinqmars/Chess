#pragma once
#include "Piece.h"

class PawnPiece : public Piece
{
	bool hasMoved;
public:
	PawnPiece(int color, std::vector<int> position);
	Piece* clone();
	void move(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], std::vector<int> destination);
	std::vector<std::vector<int>> getMoves(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], bool includeMoveOnKing = false);
};

