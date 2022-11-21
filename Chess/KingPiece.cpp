#include "KingPiece.h"

using namespace std;
using namespace Globals;

KingPiece::KingPiece(int color, std::vector<int> position)
{
	this->color = color;
	this->position = position;
	displayedChar = 'K';
}

vector<vector<int>> KingPiece::getMoves(BoardSpace board[BOARD_SIZE][BOARD_SIZE])
{
	int currentPosX = position[0];
	int currentPosY = position[1];
	vector<vector<int>> possibleMoves;
	vector<vector<int>> movementVector =
	{
		{0, 1},
		{0, -1},
		{-1, 0},
		{1, 0},
		{1, 1},
		{-1, 1},
		{1, -1},
		{-1, -1},
	};

	for (int i = 0; i < movementVector.size(); i++)
	{
		int moveX = movementVector[i][0];
		int destPosX = currentPosX + moveX;
		int moveY = movementVector[i][1];
		int destPosY = currentPosY + moveY;
		if (destPosX >= 0 && destPosX < BOARD_SIZE && destPosY >= 0 && destPosY < BOARD_SIZE)
		{
			Piece* destinationPiece = board[destPosX][destPosY].getPiecePtr();
			if (destinationPiece)
			{
				if (destinationPiece->getDisplayedChar() != 'K')
				{
					if (destinationPiece->getColor() != color)
					{
						possibleMoves.push_back(vector<int> { destPosX, destPosY });
					}
				}
			}
			else
			{
				possibleMoves.push_back(vector<int> { destPosX, destPosY });
			}
		}
	}

	return possibleMoves;
}
