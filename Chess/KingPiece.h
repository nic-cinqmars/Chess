#pragma once
#include "Piece.h"

class KingPiece : public Piece
{
public:
	KingPiece(int color);
	Movement move();
};

