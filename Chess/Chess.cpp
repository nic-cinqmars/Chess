#define NOMINMAX

#include "Board.h"
#include <iostream>
#include <string>

using namespace std;

void IgnoreLine();

vector<int> GetPosition();

int main()
{
	Board board;
	int playerTurn = 0;
	do
	{
		board.printBoard();
		if (playerTurn == 0)
		{
			cout << "- White's turn to move -\n";
		}
		else
		{
			cout << "- Black's turn to move -\n";
		}
		bool moveWorked = false;
		do {
			cout << "Enter the position of the piece to move: ";
			vector<int> pieceToMove = GetPosition();

			cout << "Enter the position that the piece will move to: ";
			vector<int> positionToGo = GetPosition();

			moveWorked = board.attemptPieceMove(pieceToMove, playerTurn, positionToGo);
		} while (!moveWorked);
	} while (true);

	return 0;
}

//Clear extra input from cin
void IgnoreLine()
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


vector<int> GetPosition()
{
	while (true)
	{
		string input;
		cin >> input;
		if (input.length() != 2)
		{
			cout << "Input invalid, please format it properly (ex: A1)! Try again : ";
		}
		else
		{
			char charX = toupper(input[0]);
			char charY = input[1];
			if (int(charX) < 65 || int(charX) > 72)
			{
				cout << "Invalid letter '" << charX << "'. Input a letter between A and H! Try again : ";
			}
			else if (!isdigit(charY))
			{
				cout << "'" << charY << "' is not a valid number! Try again : ";
			}
			else if (charY - '0' < 1 || charY - '0' > Board::BOARD_SIZE)
			{
				cout << "'" << charY << "' is not a valid position on the board! Try again : ";
			}
			else
			{
				IgnoreLine();

				int posX = int(charX) - 65;
				int posY = charY - '1';
				vector<int> position = { posX, posY };
				return position;
			}
		}
		IgnoreLine();
	}
}