#pragma once
#include "Piece.h"

class BishopPiece : public Piece
{
public:
	BishopPiece(int color);
	Movement move();
};

