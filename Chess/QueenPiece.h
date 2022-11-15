#pragma once
#include "Piece.h"

class QueenPiece : public Piece
{
public:
	QueenPiece(int color);
	void move();
};

