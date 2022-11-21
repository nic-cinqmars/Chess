#include "PawnPiece.h"

using namespace std;
using namespace Globals;

PawnPiece::PawnPiece(int color, std::vector<int> position)
{
	this->color = color;
	this->position = position;
	displayedChar = 'P';
	hasMoved = false;
}

vector<vector<int>> PawnPiece::getMoves(BoardSpace board[BOARD_SIZE][BOARD_SIZE])
{
	int currentPosX = position[0];
	int currentPosY = position[1];
	vector<vector<int>> possibleMoves;
	if (color == 0)
	{
		if (!hasMoved)
		{
			Piece* upPiece = board[currentPosX][currentPosY + 2].getPiecePtr();
			if (!upPiece)
			{
				possibleMoves.push_back({ currentPosX, currentPosY + 2 });
			}
		}

		if (currentPosY + 1 < BOARD_SIZE)
		{
			Piece* upPiece = board[currentPosX][currentPosY + 1].getPiecePtr();
			if (!upPiece)
			{
				possibleMoves.push_back({ currentPosX, currentPosY + 1 });
			}
		}

		// Check if other color piece on diagonal
		int diagonalRightX = currentPosX + 1;
		int diagonalLeftX = currentPosX - 1;
		int diagonalY = currentPosY + 1;
		if (diagonalY < BOARD_SIZE)
		{
			if (diagonalRightX < BOARD_SIZE)
			{
				Piece* diagonalRightPiece = board[diagonalRightX][diagonalY].getPiecePtr();
				if (diagonalRightPiece)
				{
					if (diagonalRightPiece->getColor() != color)
					{
						possibleMoves.push_back({ currentPosX + 1, currentPosY + 1 });
					}
				}
			}
			if (diagonalLeftX >= 0)
			{
				Piece* diagonalLeftPiece = board[diagonalLeftX][diagonalY].getPiecePtr();
				if (diagonalLeftPiece)
				{
					if (diagonalLeftPiece->getColor() != color)
					{
						possibleMoves.push_back({ currentPosX - 1, currentPosY + 1 });
					}
				}
			}
		}
	}
	else
	{
		if (!hasMoved)
		{
			Piece* downPiece = board[currentPosX][currentPosY - 2].getPiecePtr();
			if (!downPiece)
			{
				possibleMoves.push_back({ currentPosX, currentPosY - 2 });
			}
		}

		if (currentPosY - 1 >= 0)
		{
			Piece* downPiece = board[currentPosX][currentPosY - 1].getPiecePtr();
			if (!downPiece)
			{
				possibleMoves.push_back({ currentPosX, currentPosY - 1 });
			}
		}

		// Check if other color piece on diagonal
		int diagonalRightX = currentPosX + 1;
		int diagonalLeftX = currentPosX - 1;
		int diagonalY = currentPosY - 1;
		if (diagonalY >= 0)
		{
			if (diagonalRightX < BOARD_SIZE)
			{
				Piece* diagonalRightPiece = board[diagonalRightX][diagonalY].getPiecePtr();
				if (diagonalRightPiece)
				{
					if (diagonalRightPiece->getColor() != color)
					{
						possibleMoves.push_back({ currentPosX + 1, currentPosY - 1 });
					}
				}
			}
			if (diagonalLeftX >= 0)
			{
				Piece* diagonalLeftPiece = board[diagonalLeftX][diagonalY].getPiecePtr();
				if (diagonalLeftPiece)
				{
					if (diagonalLeftPiece->getColor() != color)
					{
						possibleMoves.push_back({ currentPosX - 1, currentPosY - 1 });
					}
				}
			}
		};
	}

	return possibleMoves;
}

void PawnPiece::move(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE], std::vector<int> destination)
{
	Piece::move(board, destination);
	if (!hasMoved)
	{
		hasMoved = true;
	}
}
