#include "BoardSpace.h"

BoardSpace::BoardSpace()
{
	color = 0;
	this->piecePtr = new EmptyPiece();
}

BoardSpace::BoardSpace(int color)
{
	this->color = color;
	this->piecePtr = new EmptyPiece();
}

BoardSpace::BoardSpace(int color, Piece* piece)
{
	this->color = color;
	this->piecePtr = piece;
}

int BoardSpace::getColor()
{
	return color;
}

Piece* BoardSpace::getPiecePtr()
{
	return piecePtr;
}
