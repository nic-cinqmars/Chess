#pragma once
#include "Piece.h"

class PawnPiece : public Piece
{
public:
	PawnPiece(int color);
	void move();
};

