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
	// Sets the space of the old position to point to no piece
	board[position[0]][position[1]].setPiecePtr(nullptr);

	// Moves the piece
	position[0] = destination[0];
	position[1] = destination[1];

	// Sets the space of the new position to point to this piece
	board[destination[0]][destination[1]].setPiecePtr(this);
}

bool Piece::checkForCheck(BoardSpace board[Globals::BOARD_SIZE][Globals::BOARD_SIZE])
{
	// Gets the moves that this piece can do, including ones that would move the piece on top of the opposing king
	vector<vector<int>> possibleMoves = getMoves(board, true);

	// Loops through every move to check if the move lands on the opposing king
	for (int i = 0; i < possibleMoves.size(); i++)
	{
		int moveX = possibleMoves[i][0];
		int moveY = possibleMoves[i][1];

		Piece* possiblePiece = board[moveX][moveY].getPiecePtr();
		// Checks if this move lands on a piece
		if (possiblePiece)
		{
			// Checks if the piece that we land on is the king
			if (possiblePiece->getDisplayedChar() == 'K')
			{
				// If it is, return true
				return true;
			}
		}
	}
	// If no moves land on the opposing king, return false.
	return false;
}
