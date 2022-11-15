#pragma once
#include "Piece.h"
#include "EmptyPiece.h"

class BoardSpace
{
	int color;
	Piece *piecePtr;

public:
	BoardSpace();

	BoardSpace(int color);

	BoardSpace(int color, Piece* piece);

	int getColor();

	Piece* getPiecePtr();
};

