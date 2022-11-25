#pragma once
class Piece;
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

	void setPiecePtr(Piece* piece);
};