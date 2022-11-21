#include "Piece.h"

using namespace std;

int Piece::getColor()
{
	return color;
}

char Piece::getDisplayedChar()
{
	return displayedChar;
}

vector<int> Piece::getPosition()
{
	return position;
}

void Piece::move(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], std::vector<int> destination)
{
	board[position[0]][position[1]].setPiecePtr(nullptr);
	position[0] = destination[0];
	position[1] = destination[1];
	board[destination[0]][destination[1]].setPiecePtr(this);
}
