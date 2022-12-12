#include "KingPiece.h"

using namespace std;
using namespace Globals;

KingPiece::KingPiece(int color, std::vector<int> position)
{
	this->color = color;
	this->position = position;
	hasMoved = false;
	displayedChar = 'K';
}

Piece* KingPiece::clone()
{
	return new KingPiece(color, position);
}

vector<vector<int>> KingPiece::getMoves(BoardSpace board[BOARD_SIZE][BOARD_SIZE], bool includeMoveOnKing)
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
			BoardSpace* spaceToMoveTo = &board[destPosX][destPosY];

			Piece* destinationPiece = board[destPosX][destPosY].getPiecePtr();
			if (destinationPiece)
			{
				if (destinationPiece->getColor() != color)
				{
					possibleMoves.push_back(vector<int> { destPosX, destPosY });
				}
			}
			else
			{
				possibleMoves.push_back(vector<int> { destPosX, destPosY });
			}
		}
	}

	// Check if castling move is possible
	if (!hasMoved)
	{
		RookPiece* leftRook = dynamic_cast<RookPiece*>(board[0][currentPosY].getPiecePtr());
		if (leftRook)
		{
			if (!leftRook->getHasMoved())
			{
				bool noPieces = true;

				for (int i = currentPosX - 1; i > 0; i--)
				{
					Piece* piece = board[i][currentPosY].getPiecePtr();
					if (piece)
					{
						noPieces = false;
						break;
					}
				}

				if (noPieces)
				{
					possibleMoves.push_back(vector<int> { currentPosX - 2, currentPosY });
				}
			}
		}

		RookPiece* rightRook = dynamic_cast<RookPiece*>(board[BOARD_SIZE - 1][currentPosY].getPiecePtr());
		if (rightRook)
		{
			if (!rightRook->getHasMoved())
			{
				bool noPieces = true;

				for (int i = currentPosX + 1; i < BOARD_SIZE - 1; i++)
				{
					Piece* piece = board[i][currentPosY].getPiecePtr();
					if (piece)
					{
						noPieces = false;
						break;
					}
				}

				if (noPieces)
				{
					possibleMoves.push_back(vector<int> { currentPosX + 2, currentPosY });
				}
			}
		}
	}

	return possibleMoves;
}

void KingPiece::move(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], std::vector<int> destination)
{
	if (!hasMoved)
	{
		hasMoved = true;
	}
	Piece::move(board, destination);
}

bool KingPiece::getHasMoved()
{
	return hasMoved;
}

void KingPiece::setHasMoved(bool value)
{
	hasMoved = value;
}