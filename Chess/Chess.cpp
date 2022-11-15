#define NOMINMAX

#include "Board.h"
#include <iostream>
#include <string>

using namespace std;

void IgnoreLine();

int* GetPosition();

int main()
{
	Board board;
	board.printBoard();
	do
	{
		int* position;
		position = GetPosition();
		board.checkPossibleMoves(*position, *(position + 1));
	} while (true);

	return 0;
}

//Clear extra input from cin
void IgnoreLine()
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


int* GetPosition()
{
	while (true)
	{
		string input;
		cin >> input;
		if (input.length() != 2)
		{
			cout << "Input invalid, please format it properly (Ex: A1)! Try again : ";
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
			else if (charY - '0' < 0 || charY - '0' > Board::BOARD_SIZE)
			{
				cout << "'" << charY << "' is not a valid position on the board! Try again : ";
			}
			else
			{
				IgnoreLine();

				int posX = int(charX) - 65;
				int posY = charY - '0';
				cout << "Pos x: " << posX << " Pos y: " << posY;
				int position[] = { posX, posY };
				return position;
			}
		}
		IgnoreLine();
	}
}