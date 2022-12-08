#define NOMINMAX
#define _WIN32_WINNT 0x0500

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include "Board.h"
#include "invalid_move.h"
#include "load_game.h"

using namespace std;
using namespace Globals;

void IgnoreLine();

string GetTimeFromDuration(chrono::duration<double> time);

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
	
	chrono::duration<double> lastTurnTime;
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
			string oldPlayerString;
			int oldPlayer = playerTurn;
			if (playerTurn == 0)
			{
				oldPlayerString = "White";
				playerTurn++;
			}
			else
			{
				oldPlayerString = "Black";
				playerTurn = 0;
			}
			board.printBoard(playerTurn);
			board.clearEnPassant(playerTurn);
			cout << oldPlayerString << " took " << GetTimeFromDuration(lastTurnTime) << " to make this move.\n";
			cout << oldPlayerString << "'s total reflection time is now " << GetTimeFromDuration(board.getTime(oldPlayer)) << ".\n\n";
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
		bool moveWorked = false;
		do {
			//board.checkAllColorPieceMoves(0);
			vector<int> pieceToMovePosition;
			vector<int> positionToGo;
			try
			{
				cout << "Enter the position of the piece to move: ";
				pieceToMovePosition = GetPosition();

				cout << "Enter the position that the piece will move to: ";
				positionToGo = GetPosition();
			}
			catch (load_game* e)
			{
				cout << e->what();
				board.loadGame(&playerTurn);
				newGameLoaded = true;
				break;
			}

			try
			{
				board.attemptPieceMove(pieceToMovePosition, playerTurn, positionToGo);
				moveWorked = true;
			}
			catch (invalid_move* e)
			{
				cout << "Invalid move: ";
				cout << e->what();
				cout << " Try again...\n";
			}

			if (moveWorked)
			{
				lastTurnTime = board.setTime(playerTurn);
			}
		} while (!moveWorked);
	} while (!board.isCheckmate());

	board.printBoard(playerTurn);

	chrono::duration<double> whiteTime = board.getTime(0);
	chrono::duration<double> blackTime = board.getTime(1);
	chrono::duration<double> totalTime = whiteTime + blackTime;
	cout << "Checkmate!\n";
	cout << "Game lasted " << GetTimeFromDuration(totalTime) << ".\n";
	cout << "White took " << GetTimeFromDuration(whiteTime) << " to think.\n";
	cout << "Black took " << GetTimeFromDuration(blackTime) << " to think.\n\n";

	cout << "Move history:";
	vector<string> moveHistory = board.getMoveHistory();
	for (int i = 0; i < moveHistory.size(); i++)
	{
		cout << "\n\t" << moveHistory[i];
	}

	return 0;
}

string GetTimeFromDuration(chrono::duration<double> time)
{
	string timeString = "";
	auto seconds = chrono::duration_cast<chrono::seconds>(time);
	auto hours = chrono::duration_cast<chrono::hours>(seconds);
	seconds -= hours;
	auto minutes = chrono::duration_cast<chrono::minutes>(seconds);
	seconds -= minutes;

	int count = 0;
	if (hours >= 1h)
	{
		count++;
	}
	if (minutes >= 1min)
	{
		count++;
	}
	if (seconds >= 1s)
	{
		count++;
	}

	if (hours >= 1h)
	{
		timeString += to_string(hours.count());
		timeString += " hour";
		if (hours >= 2h)
		{
			timeString += "s";
		}
		if (count > 1)
		{
			timeString += ", ";
		}
		count--;
	}

	if (minutes >= 1min)
	{
		timeString += to_string(minutes.count());
		timeString += " minute";
		if (minutes >= 2min)
		{
			timeString += "s";
		}
		if (count > 1)
		{
			timeString += ", ";
		}
	}

	if (seconds >= 1s)
	{
		timeString += to_string(seconds.count());
		timeString += " second";
		if (seconds >= 2s)
		{
			timeString += "s";
		}
	}

	size_t lastComma = timeString.find_last_of(',');
	if (lastComma != string::npos)
	{
		timeString.replace(lastComma, 2, " and ");
	}

	return timeString;
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
					throw new load_game();
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