#pragma once
#include "Piece.h"

class KnightPiece : public Piece
{
public:
	KnightPiece(int color);
	Movement move();
};

