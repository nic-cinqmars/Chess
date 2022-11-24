#pragma once
class Piece;
class BoardSpace
{
	int color;
	Piece *piecePtr;
	int guardedByKing;

public:
	BoardSpace();

	BoardSpace(int color);

	BoardSpace(int color, Piece* piece);

	int getColor();

	Piece* getPiecePtr();

	void setPiecePtr(Piece* piece);

	bool isGuardedByEnemyKing(int king);

	void setGuardedByKing(int king);
};

