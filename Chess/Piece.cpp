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

bool Piece::checkForCheck(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE])
{
	vector<vector<int>> possibleMoves = getMoves(board, true);
	for (int i = 0; i < possibleMoves.size(); i++)
	{
		int moveX = possibleMoves[i][0];
		int moveY = possibleMoves[i][1];

		Piece* possiblePiece = board[moveX][moveY].getPiecePtr();
		if (possiblePiece)
		{
			if (possiblePiece->getDisplayedChar() == 'K')
			{
				return true;
			}
		}
	}
	return false;
}
