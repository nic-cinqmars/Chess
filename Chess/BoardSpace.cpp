#include "BoardSpace.h"

BoardSpace::BoardSpace()
{
	color = 0;
	piecePtr = nullptr;
}

BoardSpace::BoardSpace(int color)
{
	this->color = color;
	piecePtr = nullptr;
}

BoardSpace::BoardSpace(int color, Piece* piece)
{
	this->color = color;
	piecePtr = piece;
}

int BoardSpace::getColor()
{
	return color;
}

Piece* BoardSpace::getPiecePtr()
{
	return piecePtr;
}

void BoardSpace::setPiecePtr(Piece* piece)
{
	piecePtr = piece;
}
