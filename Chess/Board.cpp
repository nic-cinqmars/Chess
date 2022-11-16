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
			else if (i == 1)
			{
				spaces[i][j] = BoardSpace(spaceColor, new PawnPiece(0));
			}
			else if (i == 6)
			{
				spaces[i][j] = BoardSpace(spaceColor, new PawnPiece(1));
			}
			else if (i == 7)
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
			Piece *piecePtr = spaces[(BOARD_SIZE - 1) - i / BOARD_DISPLAY_MAGNITUDE][j / BOARD_DISPLAY_MAGNITUDE].getPiecePtr();
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

bool Board::attemptPieceMove(vector<int> pieceToMove, int player, vector<int> destination)
{
	bool success = false;
	int posX = pieceToMove[0];
	int posY = pieceToMove[1];
	Piece* piecePtr = spaces[posY][posX].getPiecePtr();
	if (!piecePtr->isEmpty())
	{
		if (player != piecePtr->getColor())
		{
			cout << "Cannot move another players piece!\n";
			return success;
		}

		Movement pieceMovement = piecePtr->move();
		vector<vector<int>> movementVector = pieceMovement.getMovementVector();
		vector<vector<int>> possibleMovements;
		for (int i = 0; i < movementVector.size(); i++)
		{
			int moveX = movementVector[i][0];
			int destPosX = posX + moveX;
			int moveY = movementVector[i][1];
			int destPosY = posY + moveY;
			if (destPosX >= 0 && destPosX < BOARD_SIZE && destPosY >= 0 && destPosY < BOARD_SIZE)
			{
				Piece* destinationPiecePtr = spaces[destPosY][destPosX].getPiecePtr();
				if (!destinationPiecePtr->isEmpty())
				{
					if (destinationPiecePtr->getColor() != piecePtr->getColor())
					{
						if (typeid(*destinationPiecePtr).name() != "KingPiece")
						{
							vector<int> position = { destPosX, destPosY };
							possibleMovements.push_back(position);
							if (position[0] == destination[0] && position[1] == destination[1])
							{
								movePiece(pieceToMove, destination);
								success = true;
							}
						}
					}
				}
				else
				{
					vector<int> position = { destPosX, destPosY };
					possibleMovements.push_back(position);
					if (position[0] == destination[0] && position[1] == destination[1])
					{
						movePiece(pieceToMove, destination);
						success = true;
					}
				}
			}
		}
		for (int i = 0; i < possibleMovements.size(); i++)
		{
			cout << "Move : " << possibleMovements[i][0] << possibleMovements[i][1] << "\n";
		}
	}
	else
	{
		cout << "No piece to move at this position!\n";
	}
	return success;
}

void Board::movePiece(std::vector<int> originalPosition, std::vector<int> newPosition)
{
	int originalX = originalPosition[0];
	int originalY = originalPosition[1];
	Piece* originalPiecePtr = spaces[originalY][originalX].getPiecePtr();

	int newX = newPosition[0];
	int newY = newPosition[1];

	spaces[newY][newX] = BoardSpace(spaces[newY][newX].getColor(), originalPiecePtr);

	spaces[originalY][originalX] = BoardSpace(spaces[originalY][originalX].getColor());
}
