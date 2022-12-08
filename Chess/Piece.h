#pragma once
#include <vector>
#include "BoardSpace.h"
#include "Globals.h"

class Piece
{
protected:
	// The color of a piece.
	int color;

	// The char that represents a piece.
	char displayedChar;

	// The position of a piece.
	std::vector<int> position;

public:
	// Returns the possible moves that a piece can do.
	virtual std::vector<std::vector<int>> getMoves(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], bool includeMoveOnKing = false) = 0;

	// Creates and returns a copy of a piece.
	virtual Piece* clone() = 0;

	// Moves a piece to a new position on the board.
	virtual void move(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], std::vector<int> destination);

	// Checks if a piece puts the opposing king in check.
	// Returns true if a piece puts the king in check.
	// Returns false if a piece does not put the king in check.
	bool checkForCheck(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE]);

	// Returns the color of a piece.
	int getColor();

	// Returns the char of a piece.
	char getDisplayedChar();

	// Returns the positon of a piece.
	std::vector<int> getPosition();
};

