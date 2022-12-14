#include "RookPiece.h"
#include <iostream>

using namespace std;
using namespace Globals;

RookPiece::RookPiece(int color, vector<int> position)
{
	this->color = color;
	this->position = position;
	hasMoved = false;
	displayedChar = 'R';
}

Piece* RookPiece::clone()
{
	return new RookPiece(color, position);
}

vector<vector<int>> RookPiece::getMoves(BoardSpace board[BOARD_SIZE][BOARD_SIZE], bool includeMoveOnKing)
{
	int currentPosX = position[0];
	int currentPosY = position[1];
	vector<vector<int>> possibleMoves;
	vector<vector<int>> movementVector =
	{
		{0, 1},
		{0, -1},
		{1, 0},
		{-1, 0}
	};
	for (int i = 0; i < movementVector.size(); i++)
	{
		int moveX = movementVector[i][0];
		int destPosX = currentPosX + moveX;
		int moveY = movementVector[i][1];
		int destPosY = currentPosY + moveY;
		while (destPosX >= 0 && destPosX < BOARD_SIZE && destPosY >= 0 && destPosY < BOARD_SIZE)
		{
			Piece* destinationPiece = board[destPosX][destPosY].getPiecePtr();
			if (destinationPiece)
			{
				if (destinationPiece->getDisplayedChar() != 'K' || includeMoveOnKing)
				{
					if (destinationPiece->getColor() != color)
					{
						possibleMoves.push_back(vector<int> { destPosX, destPosY });
					}
				}
				break;
			}
			else
			{
				possibleMoves.push_back(vector<int> { destPosX, destPosY });
			}
			destPosX += moveX;
			destPosY += moveY;
		}
	}
	return possibleMoves;
}

void RookPiece::move(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], std::vector<int> destination)
{
	if (!hasMoved)
	{
		hasMoved = true;
	}
	Piece::move(board, destination);
}

bool RookPiece::getHasMoved()
{
	return hasMoved;
}

void RookPiece::setHasMoved(bool value)
{
	hasMoved = value;
}