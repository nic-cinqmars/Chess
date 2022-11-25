#include "Board.h"
#define FOREGROUND_WHITE		(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_BLACK		0
#define BACKGROUND_WHITE		(BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN)
#define BACKGROUND_BLACK		0

using namespace std;
using namespace Globals;

Board::Board()
{
	checkmate = false;
	check = false;

	string initialBoard[BOARD_SIZE][BOARD_SIZE] =
	{
		{"R1", "n1", "B1", "Q1", "K1", "B1", "n1", "R1"},
		{"P1", "P1", "P1", "P1", "P1", "P1", "P1", "P1"},
		{"X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X"},
		{"P0", "P0", "P0", "P0", "P0", "P0", "P0", "P0"},
		{"R0", "n0", "B0", "Q0", "K0", "B0", "n0", "R0"}
	};

	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			int spaceColor = (x + y) % 2;
			spaces[x][y] = BoardSpace(spaceColor);
		}
	}

	loadBoardFromString(initialBoard);
}

void Board::clearBoard()
{
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			int spaceColor = (x + y) % 2;
			spaces[x][y] = BoardSpace(spaceColor);
		}
	}
	whitePieces.clear();
	blackPieces.clear();
	moveHistory.clear();
}

void Board::loadBoardFromString(string board[BOARD_SIZE][BOARD_SIZE])
{
	clearBoard();

	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			int currentY = (BOARD_SIZE - 1) - y;
			string currentPiece = board[currentY][x];
			if (currentPiece.length() == 2)
			{
				int pieceColor = currentPiece[1] - '0';
				if (pieceColor == 0 || pieceColor == 1)
				{
					Piece* piece = nullptr;

					switch (currentPiece[0])
					{
					case 'P':
						piece = new PawnPiece(pieceColor, vector<int> {x, y});
						break;
					case 'R':
						piece = new RookPiece(pieceColor, vector<int> {x, y});
						break;
					case 'n':
						piece = new KnightPiece(pieceColor, vector<int> {x, y});
						break;
					case 'B':
						piece = new BishopPiece(pieceColor, vector<int> {x, y});
						break;
					case 'Q':
						piece = new QueenPiece(pieceColor, vector<int> {x, y});
						break;
					case 'K':
						piece = new KingPiece(pieceColor, vector<int> {x, y});
						if (pieceColor == 0)
						{
							whiteKing = dynamic_cast<KingPiece*>(piece);
						}
						else
						{
							blackKing = dynamic_cast<KingPiece*>(piece);
						}
						break;
					default:
						break;
					}

					if (piece)
					{
						addPiece(piece);
						spaces[x][y].setPiecePtr(piece);
					}
				}
			}
		}
	}
}

void Board::saveGame(int* player)
{
	ofstream file;
	file.open("game.txt");
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			Piece* piece = spaces[x][(BOARD_SIZE - 1) - y].getPiecePtr();
			if (piece)
			{
				file << piece->getDisplayedChar() << piece->getColor();
			}
			else
			{
				file << "X";
			}
			if (x != (BOARD_SIZE - 1))
			{
				file << " ";
			}
		}
		file << "\n";
	}
	file << *player;
	file.close();
}

void Board::loadGame(int* player)
{
	ifstream file("game.txt");
	string savedBoard[BOARD_SIZE][BOARD_SIZE];

	if (file.is_open())
	{
		string line;
		int indexY = 0;
		while (getline(file, line))
		{
			if (indexY < BOARD_SIZE)
			{
				int indexX = 0;
				while (line.find(" ") != string::npos)
				{
					if (indexX < BOARD_SIZE)
					{
						savedBoard[indexY][indexX] = line.substr(0, line.find(" "));
						line.erase(0, line.find(" ") + 1);
						indexX++;
					}
				}
				savedBoard[indexY][indexX] = line;
				indexY++;
			}
			else if (indexY == BOARD_SIZE)
			{
				*player = line[0] - '0';
			}
		}
	}

	loadBoardFromString(savedBoard);
}

std::vector<Piece*> Board::getPieces(int color)
{
	if (color == 0)
	{
		return whitePieces;
	}
	else
	{
		return blackPieces;
	}
}

void Board::addPiece(Piece* piece)
{
	if (piece->getColor() == 0)
	{
		whitePieces.push_back(piece);
	}
	else
	{
		blackPieces.push_back(piece);
	}
}

void Board::checkAllColorPieceMoves(int color)
{
	if (color == 0)
	{
		for (int i = 0; i < whitePieces.size(); i++)
		{
			cout << whitePieces[i]->getDisplayedChar() << " (W) at " << whitePieces[i]->getPosition()[0] << "," << whitePieces[i]->getPosition()[1] << "\n";
			vector<vector<int>> moves = whitePieces[i]->getMoves(spaces);
			for (int j = 0; j < moves.size(); j++)
			{
				cout << "\t" << moves[j][0] << " " << moves[j][1] << "\n";
			}
		}
	}
	else
	{
		for (int i = 0; i < blackPieces.size(); i++)
		{
			cout << blackPieces[i]->getDisplayedChar() << " (B) at " << blackPieces[i]->getPosition()[0] << "," << blackPieces[i]->getPosition()[1] << "\n";
			vector<vector<int>> moves = blackPieces[i]->getMoves(spaces);
			for (int j = 0; j < moves.size(); j++)
			{
				cout << "\t" << moves[j][0] << " " << moves[j][1] << "\n";
			}
		}
	}
}

void Board::printBoard(int color)
{
	system("CLS");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO baseColor;
	GetConsoleScreenBufferInfo(hConsole, &baseColor);
	for (int y = 0; y < BOARD_SIZE * BOARD_DISPLAY_MAGNITUDE; y++)
	{
		if (y != 0)
		{
			cout << "\n";
		}
		bool emptyRow = ((y - BOARD_DISPLAY_MAGNITUDE / 2) % BOARD_DISPLAY_MAGNITUDE) != 0;
		for (int x = 0; x < BOARD_SIZE * BOARD_DISPLAY_MAGNITUDE; x++)
		{
			int pieceX = x / BOARD_DISPLAY_MAGNITUDE;
			int pieceY = y / BOARD_DISPLAY_MAGNITUDE;
			if (color == 0)
			{
				pieceY = (BOARD_SIZE - 1) - pieceY;
			}
			else
			{
				pieceX = (BOARD_SIZE - 1) - pieceX;
			}
			Piece *piecePtr = spaces[pieceX][pieceY].getPiecePtr();

			char piece;
			int pieceColor;
			if (piecePtr)
			{
				piece = piecePtr->getDisplayedChar();
				pieceColor = piecePtr->getColor();
			}
			else
			{
				piece = ' ';
				pieceColor = spaces[x / BOARD_DISPLAY_MAGNITUDE][y / BOARD_DISPLAY_MAGNITUDE].getColor();
			}

			if (spaces[x / BOARD_DISPLAY_MAGNITUDE][y / BOARD_DISPLAY_MAGNITUDE].getColor() == 1)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE | BACKGROUND_BLACK);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLACK | BACKGROUND_WHITE);
			}
			if (!emptyRow)
			{
				bool placeEmpty = (x - BOARD_DISPLAY_MAGNITUDE / 2) % BOARD_DISPLAY_MAGNITUDE != 0;
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
				// Display coordinates with certain checks
				if (x == 0 && (y + 1) % BOARD_DISPLAY_MAGNITUDE == 0)
				{
					cout << " " << pieceY + 1 << " ";
				}
				else if (y == (BOARD_SIZE * BOARD_DISPLAY_MAGNITUDE - 1) && (x + 1) % BOARD_DISPLAY_MAGNITUDE == 0)
				{
					cout << " " << char('a' + pieceX) << " ";
				}
				else
				{
					cout << "   ";
				}
			}
		}
	}
	SetConsoleTextAttribute(hConsole, baseColor.wAttributes);
	cout << "\n";
}

vector<string> Board::getMoveHistory()
{
	return moveHistory;
}

void Board::getPieceMoves(vector<int> piecePosition)
{
	Piece* piecePtr = spaces[piecePosition[0]][piecePosition[1]].getPiecePtr();

	if (piecePtr)
	{
		vector<vector<int>> movement = piecePtr->getMoves(spaces);
		for (int i = 0; i < movement.size(); i++)
		{
			cout << "Move : " << movement[i][0] << " " << movement[i][1] << "\n";
		}
	}
	else
	{
		cout << "No piece at this location!";
	}
}

bool Board::attemptPieceMove(vector<int> pieceToMovePosition, int player, vector<int> destination)
{
	bool success = false;
	Piece* pieceToMove = spaces[pieceToMovePosition[0]][pieceToMovePosition[1]].getPiecePtr();
	if (pieceToMove)
	{
		int pieceColor = pieceToMove->getColor();
		if (pieceColor == player)
		{
			vector<vector<int>> pieceMoves = pieceToMove->getMoves(spaces);
			for (int i = 0; i < pieceMoves.size(); i++)
			{
				int moveX = pieceMoves[i][0];
				int moveY = pieceMoves[i][1];
				if (destination[0] == moveX && destination[1] == moveY)
				{
					if (!willPutInCheck(pieceToMove, destination))
					{
						check = false;
						movePiece(pieceToMove, destination);
						success = true;
					}
					else
					{
						break;
					}
				}
			}
		}
		else
		{
			cout << "Cannot move another player's piece!";
		}
	}
	else
	{
		cout << "No piece at this position!";
	}
	return success;
}

bool Board::willPutInCheck(Piece* pieceToMove, std::vector<int> destination)
{
	bool check = false;
	vector<Piece*> otherColorPieces;
	if (pieceToMove->getColor() == 0)
	{
		otherColorPieces = blackPieces;
	}
	else
	{
		otherColorPieces = whitePieces;
	}

	BoardSpace tempSpaces[BOARD_SIZE][BOARD_SIZE];
	copy(&spaces[0][0], &spaces[0][0] + BOARD_SIZE * BOARD_SIZE, &tempSpaces[0][0]);
	Piece* pieceCopy = pieceToMove->clone();
	pieceCopy->move(tempSpaces, destination);
	for (int i = 0; i < otherColorPieces.size(); i++)
	{
		Piece* currentPiece = otherColorPieces[i];
		if (currentPiece->getPosition() != destination)
		{
			check = currentPiece->checkForCheck(tempSpaces);
			if (check)
			{
				break;
			}
		}
	}
	return check;
}

void Board::movePiece(Piece* pieceToMove, vector<int> newPosition)
{
	Piece* currentPiece = spaces[newPosition[0]][newPosition[1]].getPiecePtr();
	if (currentPiece)
	{
		cout << "Deleting piece : " << currentPiece->getDisplayedChar();
		if (currentPiece->getColor() == 0)
		{
			vector<Piece*>::iterator position = find(whitePieces.begin(), whitePieces.end(), currentPiece);
			whitePieces.erase(position);
		}
		else
		{
			vector<Piece*>::iterator position = find(blackPieces.begin(), blackPieces.end(), currentPiece);
			blackPieces.erase(position);
		}
	}
	string move;
	if (pieceToMove->getColor() == 0)
	{
		move.append("White ");
	}
	else
	{
		move.append("Black ");
	}

	move += pieceToMove->getDisplayedChar();
	move += ": ";

	move += char('A' + pieceToMove->getPosition()[0]);
	move.append(to_string(pieceToMove->getPosition()[1] + 1));

	move.append(" -> ");

	move += char('A' + newPosition[0]);
	move.append(to_string(newPosition[1] + 1));

	moveHistory.push_back(move);

	if (pieceToMove->getDisplayedChar() == 'P')
	{
		if (pieceToMove->getColor() == 0)
		{
			if (newPosition[1] == BOARD_SIZE - 1)
			{
				vector<Piece*>::iterator position = find(whitePieces.begin(), whitePieces.end(), pieceToMove);
				whitePieces.erase(position);
				pieceToMove = promotePawn(pieceToMove);
				whitePieces.push_back(pieceToMove);
			}
		}
		else
		{
			if (newPosition[1] == 0)
			{
				vector<Piece*>::iterator position = find(blackPieces.begin(), blackPieces.end(), pieceToMove);
				blackPieces.erase(position);
				pieceToMove = promotePawn(pieceToMove);
				blackPieces.push_back(pieceToMove);
			}
		}
	}

	pieceToMove->move(spaces, newPosition);

	check = pieceToMove->checkForCheck(spaces);
	if (check)
	{
		int otherPlayer;
		if (pieceToMove->getColor() == 0)
		{
			otherPlayer = 1;
		}
		else
		{
			otherPlayer = 0;
		}
		checkmate = checkForCheckmate(otherPlayer);
	}
}

Piece* Board::promotePawn(Piece* pawn)
{
	Piece* newPiece = nullptr;
	cout << "Enter the piece which the pawn will promote to (n, B, R or Q) : ";
	do
	{
		string input;
		cin >> input;
		if (!input.empty())
		{
			switch (toupper(input[0]))
			{
				case 'N':
					newPiece = new KnightPiece(pawn->getColor(), pawn->getPosition());
					break;
				case 'B':
					newPiece = new BishopPiece(pawn->getColor(), pawn->getPosition());
					break;
				case 'R':
					newPiece = new RookPiece(pawn->getColor(), pawn->getPosition());
					break;
				case 'Q':
					newPiece = new QueenPiece(pawn->getColor(), pawn->getPosition());
					break;
				default :
					cout << "Invalid piece! Try again : ";
					break;
			}

		}
	} while (!newPiece);
	return newPiece;
}

bool Board::checkForCheckmate(int player)
{
	bool checkmate = true;
	vector<Piece*> currentPlayerPieces = getPieces(player);
	for (int i = 0; i < currentPlayerPieces.size(); i++)
	{
		if (!checkmate)
		{
			break;
		}
		vector<vector<int>> currentPieceMoves = currentPlayerPieces[i]->getMoves(spaces);
		for (int j = 0; j < currentPieceMoves.size(); j++)
		{
			checkmate = willPutInCheck(currentPlayerPieces[i], currentPieceMoves[j]);
			if (!checkmate)
			{
				break;
			}
		}
	}
	return checkmate;
}

bool Board::isCheck()
{
	return check;
}

bool Board::isCheckmate()
{
	return checkmate;
}
