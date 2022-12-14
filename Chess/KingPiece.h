#pragma once
#include <iostream>
#include "Piece.h"
#include "RookPiece.h"

class KingPiece : public Piece
{
	bool hasMoved;
public:
	KingPiece(int color, std::vector<int> position);
	Piece* clone();
	void move(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], std::vector<int> destination);
	std::vector<std::vector<int>> getMoves(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], bool includeMoveOnKing = false);
	bool getHasMoved();
	void setHasMoved(bool value);
};