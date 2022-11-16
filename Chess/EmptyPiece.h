#pragma once
#include "Piece.h"

class EmptyPiece : public Piece
{
public:
	EmptyPiece();
	Movement move();
};

