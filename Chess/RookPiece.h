#pragma once
#include "Piece.h"

class RookPiece : public Piece
{
public:
	RookPiece(int color);
	Movement move();
};

