#pragma once
class Piece;

// BoardSpace stores a color aswell as a pointer to a piece (which can be null if there is no piece).
class BoardSpace
{
	// The color of this space, either 0 or 1.
	int color;

	// A pointer to the piece that is currently in this space.
	Piece *piecePtr;

public:
	// Creates a BoardSpace object with a color of 0 and no piece.
	BoardSpace();

	// Creates a BoardSpace object with a specified color and no piece.
	BoardSpace(int color);

	// Creates a BoardSpace object with a specified color and a specified piece.
	BoardSpace(int color, Piece* piece);

	// Returns the color of this space.
	int getColor();

	// Returns the Piece* of this space.
	Piece* getPiecePtr();

	// Sets the Piece* of this space.
	void setPiecePtr(Piece* piece);
};