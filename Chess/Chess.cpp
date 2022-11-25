#define NOMINMAX
#define _WIN32_WINNT 0x0500

#include "Board.h"
#include <iostream>
#include <string>

using namespace std;
using namespace Globals;

void IgnoreLine();

vector<int> GetPosition();

Board board;
int playerTurn = 0;

int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1000, 850, TRUE);

	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	bool newGameLoaded = true;
	do
	{
		if (newGameLoaded)
		{
			board.printBoard(playerTurn);
			cout << "Game loaded!\n";
			cout << "Welcome to chess! Follow the instructions on screen to play.\nYou can type one of these characters at any time : (S)ave, (L)oad\n";
			newGameLoaded = false;
		}
		else
		{
			if (playerTurn == 0)
			{
				playerTurn++;
			}
			else
			{
				playerTurn = 0;
			}
			board.printBoard(playerTurn);
		}
		vector<string> moveHistory = board.getMoveHistory();
		if (moveHistory.size() > 0)
		{
			cout << "Move history:\n";
			cout << "\t" << moveHistory[moveHistory.size() - 1] << "\n\n";
		}

		if (playerTurn == 0)
		{
			if (board.isCheck())
			{
				cout << "White is put in check!\n";
			}
			cout << "- White's turn to move -\n";
		}
		else
		{
			if (board.isCheck())
			{
				cout << "Black is put in check!\n";
			}
			cout << "- Black's turn to move -\n";
		}
		board.clearEnPassant(playerTurn);
		bool moveWorked = false;
		do {
			//board.checkAllColorPieceMoves(0);
			cout << "Enter the position of the piece to move: ";
			vector<int> pieceToMovePosition = GetPosition();
			if (pieceToMovePosition[0] == -1 && pieceToMovePosition[1] == -1)
			{
				newGameLoaded = true;
				break;
			}

			cout << "Enter the position that the piece will move to: ";
			vector<int> positionToGo = GetPosition();
			// Happens when new game is loaded
			if (pieceToMovePosition[0] == -1 && pieceToMovePosition[1] == -1)
			{
				newGameLoaded = true;
				break;
			}

			moveWorked = board.attemptPieceMove(pieceToMovePosition, playerTurn, positionToGo);
			if (!moveWorked)
			{
				cout << "Invalid move!\n";
			}
		} while (!moveWorked);
	} while (!board.isCheckmate());

	cout << "Checkmate!";

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
			if (input.length() == 1)
			{
				if (toupper(input[0]) == 'S')
				{
					board.saveGame(&playerTurn);
					cout << "Game saved, continue where you left off : ";
				}
				if (toupper(input[0]) == 'L')
				{
					board.loadGame(&playerTurn);
					return vector<int> { -1, -1 };
				}
			}
			else
			{
				cout << "Input invalid, please format it properly (ex: A1)! Try again : ";
			}
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
			else if (charY - '0' < 1 || charY - '0' > BOARD_SIZE)
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