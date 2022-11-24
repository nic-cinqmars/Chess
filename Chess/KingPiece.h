#pragma once
#include <iostream>
#include "Piece.h"

class KingPiece : public Piece
{
public:
	KingPiece(int color, std::vector<int> position);
	Piece* clone();
	void move(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], std::vector<int> destination);
	std::vector<std::vector<int>> getMoves(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], bool includeMoveOnKing = false);
	void setGuardedByKing(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE]);
};

