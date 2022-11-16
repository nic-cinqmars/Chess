#include "KnightPiece.h"

using namespace std;

KnightPiece::KnightPiece(int color)
{
	this->color = color;
	displayedChar = 'n';
}

Movement KnightPiece::move()
{
	vector<vector<int>> movementVector =
	{
		{-1, 2},
		{1, 2},
		{-1, -2},
		{1, -2},
		{-2, 1},
		{2, 1},
		{-2, -1},
		{2, -1},
	};
	return Movement(false, movementVector);
}