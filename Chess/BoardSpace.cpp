#include "BoardSpace.h"

BoardSpace::BoardSpace()
{
	color = 0;
	piecePtr = nullptr;
	guardedByKing = -1;
}

BoardSpace::BoardSpace(int color)
{
	this->color = color;
	piecePtr = nullptr;
	guardedByKing = -1;
}

BoardSpace::BoardSpace(int color, Piece* piece)
{
	this->color = color;
	piecePtr = piece;
	guardedByKing = -1;
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

bool BoardSpace::isGuardedByEnemyKing(int king)
{
	if (king == guardedByKing || guardedByKing == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void BoardSpace::setGuardedByKing(int king)
{
	guardedByKing = king;
}
