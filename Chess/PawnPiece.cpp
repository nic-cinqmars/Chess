#include "PawnPiece.h"

using namespace std;

PawnPiece::PawnPiece(int color)
{
	this->color = color;
	displayedChar = 'P';
}

Movement PawnPiece::move()
{
	vector<vector<int>> movementVector;
	if (color == 0)
	{
		movementVector = { { 0, 1 } };
	}
	else
	{
		movementVector = { { 0, -1 } };
	}
	return Movement(false, movementVector);
}
