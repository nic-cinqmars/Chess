#include "Board.h"
#define FOREGROUND_WHITE		(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_BLACK		0
#define BACKGROUND_WHITE		(BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN)
#define BACKGROUND_BLACK		0

using namespace std;

Board::Board()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int spaceColor = (j + i) % 2;
			if (i == 0)
			{
				Piece* piece;
				switch (j)
				{
				case 0:
					piece = new RookPiece(1);
					break;
				case 1:
					piece = new KnightPiece(1);
					break;
				case 2:
					piece = new BishopPiece(1);
					break;
				case 3:
					piece = new QueenPiece(1);
					break;
				case 4:
					piece = new KingPiece(1);
					break;
				case 5:
					piece = new BishopPiece(1);
					break;
				case 6:
					piece = new KnightPiece(1);
					break;
				default:
					piece = new RookPiece(1);
					break;
				}

				spaces[i][j] = BoardSpace(spaceColor, piece);
			}
			else if (i == 1)
			{
				spaces[i][j] = BoardSpace(spaceColor, new PawnPiece(1));
			}
			else if (i == 6)
			{
				spaces[i][j] = BoardSpace(spaceColor, new PawnPiece(0));
			}
			else if (i == 7)
			{
				Piece* piece;
				switch (j)
				{
				case 0:
					piece = new RookPiece(0);
					break;
				case 1:
					piece = new KnightPiece(0);
					break;
				case 2:
					piece = new BishopPiece(0);
					break;
				case 3:
					piece = new QueenPiece(0);
					break;
				case 4:
					piece = new KingPiece(0);
					break;
				case 5:
					piece = new BishopPiece(0);
					break;
				case 6:
					piece = new KnightPiece(0);
					break;
				default:
					piece = new RookPiece(0);
					break;
				}

				spaces[i][j] = BoardSpace(spaceColor, piece);
			}
			else
			{
				spaces[i][j] = BoardSpace(spaceColor);
			}
		}
	}
}

void Board::printBoard()
{
	system("CLS");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO baseColor;
	GetConsoleScreenBufferInfo(hConsole, &baseColor);
	for (int i = 0; i < BOARD_SIZE * BOARD_DISPLAY_MAGNITUDE; i++)
	{
		if (i != 0)
		{
			cout << "\n";
		}
		bool emptyRow = ((i - BOARD_DISPLAY_MAGNITUDE / 2) % BOARD_DISPLAY_MAGNITUDE) != 0;
		for (int j = 0; j < BOARD_SIZE * BOARD_DISPLAY_MAGNITUDE; j++)
		{
			Piece *piecePtr = spaces[i / BOARD_DISPLAY_MAGNITUDE][j / BOARD_DISPLAY_MAGNITUDE].getPiecePtr();
			char piece = piecePtr->getDisplayedChar();
			int pieceColor = piecePtr->getColor();
			if (spaces[i / BOARD_DISPLAY_MAGNITUDE][j / BOARD_DISPLAY_MAGNITUDE].getColor() == 1)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE | BACKGROUND_BLACK);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLACK | BACKGROUND_WHITE);
			}
			if (!emptyRow)
			{
				bool placeEmpty = (j - BOARD_DISPLAY_MAGNITUDE / 2) % BOARD_DISPLAY_MAGNITUDE != 0;
				if (!placeEmpty)
				{
					if (pieceColor == 1)
					{
						SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE | BACKGROUND_BLACK);
					}
					else if (pieceColor == 0)
					{
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLACK | BACKGROUND_WHITE);
					}
					cout << " " << piece << " ";
				}
				else
				{
					cout << "   ";
				}
			}
			else
			{
				cout << "   ";
			}
		}
	}
	SetConsoleTextAttribute(hConsole, baseColor.wAttributes);
	cout << "\n";
}

void Board::checkPossibleMoves(int posX, int posY)
{
	Piece* piecePtr = spaces[(BOARD_SIZE - 1) - posY][posX].getPiecePtr();
	cout << " Piece : " << piecePtr->getDisplayedChar() << " Color: " << piecePtr->getColor() << "\n";
}
