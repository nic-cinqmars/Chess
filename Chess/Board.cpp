#include "Board.h"
#define FOREGROUND_WHITE		(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_BLACK		0
#define BACKGROUND_WHITE		(BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN)
#define BACKGROUND_BLACK		0

using namespace std;
using namespace Globals;

Board::Board()
{
	// Board is set up this way initially
	// Each piece is represented by its character followed by its color (0 or 1)
	// Certain pieces like pawns, kings and rooks need additional data stored such as if they have moved or not yet (3rd number, 0 or 1)
	// Pawns need even more data stored such as if they can be en passant (4th number, 0 or 1)
	string initialBoard[BOARD_SIZE][BOARD_SIZE] =
	{
		{"R10", "n1", "B1", "Q1", "K10", "B1", "n1", "R10"},
		{"P100", "P100", "P100", "P100", "P100", "P100", "P100", "P100"},
		{"X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X"},
		{"X", "X", "X", "X", "X", "X", "X", "X"},
		{"P000", "P000", "P000", "P000", "P000", "P000", "P000", "P000"},
		{"R00", "n0", "B0", "Q0", "K00", "B0", "n0", "R00"}
	};

	// Create empty board
	createNewBoard();

	// Loads the board from string above
	loadBoardFromString(initialBoard);
}

void Board::loadGame(int* player)
{
	// First create empty board
	createNewBoard();

	// Open game.txt file
	ifstream file("game.txt");

	// Initialize 2D string array
	string savedBoard[BOARD_SIZE][BOARD_SIZE];

	if (file.is_open())
	{
		string line;
		int indexY = 0;
		while (getline(file, line))
		{
			// Add piece to savedBoard
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
			}
			// Load other game values
			else if (indexY == BOARD_SIZE)
			{
				*player = line[0] - '0';
			}
			else if (indexY == BOARD_SIZE + 1)
			{
				whiteTime = chrono::duration<double>(stod(line));
			}
			else if (indexY == BOARD_SIZE + 2)
			{
				blackTime = chrono::duration<double>(stod(line));
			}
			else if (indexY > BOARD_SIZE + 2)
			{
				moveHistory.push_back(line);
			}
			indexY++;
		}
	}
	// If we have a problem when opening the game.txt file, load default board
	else
	{
		string initialBoard[BOARD_SIZE][BOARD_SIZE] =
		{
			{"R10", "n1", "B1", "Q1", "K10", "B1", "n1", "R10"},
			{"P100", "P100", "P100", "P100", "P100", "P100", "P100", "P100"},
			{"X", "X", "X", "X", "X", "X", "X", "X"},
			{"X", "X", "X", "X", "X", "X", "X", "X"},
			{"X", "X", "X", "X", "X", "X", "X", "X"},
			{"X", "X", "X", "X", "X", "X", "X", "X"},
			{"P000", "P000", "P000", "P000", "P000", "P000", "P000", "P000"},
			{"R00", "n0", "B0", "Q0", "K00", "B0", "n0", "R00"}
		};

		for (int y = 0; y < BOARD_SIZE; y++)
		{
			for (int x = 0; x < BOARD_SIZE; x++)
			{
				savedBoard[y][x] = initialBoard[y][x];
			}
		}
		*player = 0;
	}

	loadBoardFromString(savedBoard);
}

void Board::loadBoardFromString(string board[BOARD_SIZE][BOARD_SIZE])
{
	// Loops through the 2D string array
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			// Inverse the y position to go from bottom to top
			int currentY = (BOARD_SIZE - 1) - y;

			string currentPiece = board[currentY][x];

			// If length > 1, we have a piece and a color
			if (currentPiece.length() > 1)
			{
				// Piece char is the first char in string
				char pieceChar = currentPiece[0];
				// Piece color is the second char in string
				int pieceColor = currentPiece[1] - '0';

				// Check if pieceColor is valid
				if (pieceColor == 0 || pieceColor == 1)
				{
					// If length == 2, possible pieces are Knight, Bishop or Queen
					if (currentPiece.length() == 2)
					{
						Piece* piece = nullptr;

						// Create piece depending on char
						switch (pieceChar)
						{
						case 'n':
							piece = new KnightPiece(pieceColor, vector<int> {x, y});
							break;
						case 'B':
							piece = new BishopPiece(pieceColor, vector<int> {x, y});
							break;
						case 'Q':
							piece = new QueenPiece(pieceColor, vector<int> {x, y});
							break;
						default:
							break;
						}

						if (piece)
						{
							// Add piece to vector
							addPiece(piece);

							// Add piece to corresponding space
							spaces[x][y].setPiecePtr(piece);
						}
					}
					// If length == 3, possible pieces are Rook and King
					else if (currentPiece.length() == 3)
					{
						// Has moved value is third char in string
						int hasMoved = currentPiece[2] - '0';
						Piece* piece = nullptr;

						if (pieceChar == 'K')
						{
							KingPiece* king = new KingPiece(pieceColor, vector<int> {x, y});
							if (hasMoved == 1)
							{
								king->setHasMoved(true);
							}
							piece = king;
						}
						else if (pieceChar == 'R')
						{
							RookPiece* rook = new RookPiece(pieceColor, vector<int> {x, y});
							if (hasMoved == 1)
							{
								rook->setHasMoved(true);
							}
							piece = rook;
						}

						if (piece)
						{
							addPiece(piece);
							spaces[x][y].setPiecePtr(piece);
						}
					}
					// If length == 4, we know the piece is a pawn
					else if (currentPiece.length() == 4)
					{
						// Has moved value is third char in string
						int hasMoved = currentPiece[2] - '0';
						// Is en passant value is fourth char in string
						int isEnPassant = currentPiece[3] - '0';

						PawnPiece* pawn = new PawnPiece(pieceColor, vector<int> {x, y});
						if (hasMoved == 1)
						{
							pawn->setHasMoved(true);
						}
						if (isEnPassant == 1)
						{
							pawn->setEnPassant(true);
						}

						addPiece(pawn);
						spaces[x][y].setPiecePtr(pawn);
					}
				}
			}
		}
	}
}

void Board::createNewBoard()
{
	// Clear every stored vector
	whitePieces.clear();
	blackPieces.clear();
	whitePawns.clear();
	blackPawns.clear();
	moveHistory.clear();

	// Initialize variables
	startTime = chrono::system_clock::now();
	whiteTime = chrono::duration<double>(0);
	blackTime = chrono::duration<double>(0);

	initializeBoardSpaces();
}

void Board::initializeBoardSpaces()
{
	// Initialize board spaces
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			int spaceColor = (x + y) % 2;
			spaces[x][y] = BoardSpace(spaceColor);
		}
	}
}

void Board::saveGame(int* player)
{
	// Open game.txt file
	ofstream file;
	file.open("game.txt");

	// Loop through spaces on the board
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			Piece* piece = spaces[x][(BOARD_SIZE - 1) - y].getPiecePtr();
			// If current space has piece
			if (piece)
			{
				// Add piece char and color to file
				file << piece->getDisplayedChar() << piece->getColor();

				// Check if piece is a pawn and add more data to file
				PawnPiece* pawn = dynamic_cast<PawnPiece*>(piece);
				if (pawn)
				{
					int hasMoved = 0;
					int isEnPassant = 0;
					if (pawn->getHasMoved())
					{
						hasMoved = 1;
					}
					if (pawn->isEnPassant())
					{
						isEnPassant = 1;
					}
					file << hasMoved << isEnPassant;
				}
				else
				{
					// Check if piece is a king and add more data to file
					KingPiece* king = dynamic_cast<KingPiece*>(piece);
					if (king)
					{
						int hasMoved = 0;
						if (king->getHasMoved())
						{
							hasMoved = 1;
						}
						file << hasMoved;
					}
					else
					{
						// Check if piece is a rook and add more data to file
						RookPiece* rook = dynamic_cast<RookPiece*>(piece);
						if (rook)
						{
							int hasMoved = 0;
							if (rook->getHasMoved())
							{
								hasMoved = 1;
							}
							file << hasMoved;
						}
					}
				}
			}
			else
			{
				// Put an X in file when the space has no piece
				file << "X";
			}
			// Check if we aren't on the last space in a row
			if (x != (BOARD_SIZE - 1))
			{
				// Add a space in file after each space on the board
				file << " ";
			}
		}
		// Add a new line to file after  each row
		file << "\n";
	}
	// Add which player's turn we are at, aswell as the reflection time of each player in the file
	file << *player << "\n";
	file << whiteTime.count() << "\n";
	file << blackTime.count();

	// Add each move in move history
	for (int i = 0; i < moveHistory.size(); i++)
	{
		file << "\n" << moveHistory[i];
	}
	// Close file
	file.close();
}

void Board::addPiece(Piece* piece)
{
	if (piece->getColor() == 0)
	{
		whitePieces.push_back(piece);
		// If the piece is a pawn, also add it to corresponding pawn vector
		if (piece->getDisplayedChar() == 'P')
		{
			PawnPiece* pawn = dynamic_cast<PawnPiece*>(piece);
			whitePawns.push_back(pawn);
		}
	}
	else
	{
		blackPieces.push_back(piece);
		// If the piece is a pawn, also add it to corresponding pawn vector
		if (piece->getDisplayedChar() == 'P')
		{
			PawnPiece* pawn = dynamic_cast<PawnPiece*>(piece);
			blackPawns.push_back(pawn);
		}
	}
}

void Board::removePiece(Piece* piece)
{
	if (piece->getColor() == 0)
	{
		vector<Piece*>::iterator position = find(whitePieces.begin(), whitePieces.end(), piece);
		whitePieces.erase(position);
		// If the piece is a pawn, also remove it from corresponding pawn vector
		if (piece->getDisplayedChar() == 'P')
		{
			PawnPiece* pawn = dynamic_cast<PawnPiece*>(piece);
			vector<PawnPiece*>::iterator position = find(whitePawns.begin(), whitePawns.end(), pawn);
			whitePawns.erase(position);
		}
	}
	else
	{
		vector<Piece*>::iterator position = find(blackPieces.begin(), blackPieces.end(), piece);
		blackPieces.erase(position);
		// If the piece is a pawn, also remove it from corresponding pawn vector
		if (piece->getDisplayedChar() == 'P')
		{
			PawnPiece* pawn = dynamic_cast<PawnPiece*>(piece);
			vector<PawnPiece*>::iterator position = find(blackPawns.begin(), blackPawns.end(), pawn);
			blackPawns.erase(position);
		}
	}
}

vector<Piece*> Board::getPieces(int color)
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

vector<PawnPiece*> Board::getPawns(int color)
{
	if (color == 0)
	{
		return whitePawns;
	}
	else
	{
		return blackPawns;
	}
}

void Board::clearEnPassant(int color)
{
	vector<PawnPiece*> pawns = getPawns(color);
	for (int i = 0; i < pawns.size(); i++)
	{
		if (pawns[i]->isEnPassant())
		{
			pawns[i]->setEnPassant(false);
		}
	}
}

void Board::printBoard(int color)
{
	// Clear console
	system("CLS");

	// Get console HANDLE
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get base color of console
	CONSOLE_SCREEN_BUFFER_INFO baseColor;
	GetConsoleScreenBufferInfo(hConsole, &baseColor);

	// Loop through board y
	for (int y = 0; y < BOARD_SIZE * BOARD_DISPLAY_MAGNITUDE; y++)
	{
		// Add new line if we aren't on first line
		if (y != 0)
		{
			cout << "\n";
		}

		// Checks if row will be empty
		bool emptyRow = ((y - BOARD_DISPLAY_MAGNITUDE / 2) % BOARD_DISPLAY_MAGNITUDE) != 0;

		// Loop through board x
		for (int x = 0; x < BOARD_SIZE * BOARD_DISPLAY_MAGNITUDE; x++)
		{
			// Get x and y position of piece
			int pieceX = x / BOARD_DISPLAY_MAGNITUDE;
			int pieceY = y / BOARD_DISPLAY_MAGNITUDE;

			// Flip if we want to display in other orientation
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
			// Check if space has a piece
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
				// Red background and white foreground
				SetConsoleTextAttribute(hConsole, 0xCF);
			}
			else
			{
				// White background and red foreground
				SetConsoleTextAttribute(hConsole, 0xFC);
			}
			if (!emptyRow)
			{
				bool placeEmpty = (x - BOARD_DISPLAY_MAGNITUDE / 2) % BOARD_DISPLAY_MAGNITUDE != 0;
				// If we aren't on an empty x position, change console colors and display piece
				if (!placeEmpty)
				{
					if (piece != ' ')
					{
						if (pieceColor == 1)
						{
							// Black background and dark white foreground
							SetConsoleTextAttribute(hConsole, 0x07);
						}
						else if (pieceColor == 0)
						{
							// Dark white background and black foreground
							SetConsoleTextAttribute(hConsole, 0x70);
						}
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
				// If we are on an empty row, do some checks to display coordinates
				if (x == 0 && (y + 1) % BOARD_DISPLAY_MAGNITUDE == 0)
				{
					cout << " " << pieceY + 1 << " ";
				}
				else if (y == (BOARD_SIZE * BOARD_DISPLAY_MAGNITUDE - 1) && (x + 1) % BOARD_DISPLAY_MAGNITUDE == 0)
				{
					cout << " " << char('a' + pieceX) << " ";
				}
				// If we don't display coordinates, just put three spaces
				else
				{
					cout << "   ";
				}
			}
		}
	}
	// Set console color back to original color
	SetConsoleTextAttribute(hConsole, baseColor.wAttributes);
	cout << "\n";
}

void Board::attemptPieceMove(vector<int> pieceToMovePosition, int player, vector<int> destination)
{
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
					// Check for castling rules
					KingPiece* kingPiece = dynamic_cast<KingPiece*>(pieceToMove);
					if (kingPiece)
					{
						// Check for castle
						if (!kingPiece->getHasMoved())
						{
							int castleX = destination[0] - pieceToMovePosition[0];
							// Castling
							if (abs(castleX) == 2)
							{
								if (check)
								{
									break;
								}
								else
								{
									if (castleX > 0)
									{
										castleX--;
									}
									else if (castleX < 0)
									{
										castleX++;
									}
									if (willPutInCheck(kingPiece, vector<int>{pieceToMovePosition[0] + castleX, pieceToMovePosition[1]}))
									{
										throw new invalid_move("Cannot castle if one of the spaces the king goes through will put it in check!");
									}
								}
							}
						}
					}

					if (!willPutInCheck(pieceToMove, destination))
					{
						check = false;
						movePiece(pieceToMove, destination);
						return;
					}
					else
					{
						if (check)
						{
							throw new invalid_move("The king would still be in check!");
						}
						else
						{
							throw new invalid_move("This move would put the king in check!");
						}
					}
				}
			}
			throw new invalid_move("This piece cannot make this move!");
		}
		else
		{
			throw new invalid_move("Cannot move another player's piece!");
		}
	}
	else
	{
		throw new invalid_move("No piece at this position!");
	}
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
		removePiece(currentPiece);
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
				removePiece(pieceToMove);
				pieceToMove = promotePawn(pieceToMove);
				addPiece(pieceToMove);
			}
			else
			{
				PawnPiece* enPassantPawn = dynamic_cast<PawnPiece*>(spaces[newPosition[0]][newPosition[1] - 1].getPiecePtr());
				if (enPassantPawn)
				{
					if (enPassantPawn->isEnPassant())
					{
						spaces[newPosition[0]][newPosition[1] - 1].setPiecePtr(nullptr);
						removePiece(enPassantPawn);
					}
				}
			}
		}
		else
		{
			if (newPosition[1] == 0)
			{
				removePiece(pieceToMove);
				pieceToMove = promotePawn(pieceToMove);
				addPiece(pieceToMove);
			}
			else
			{
				PawnPiece* enPassantPawn = dynamic_cast<PawnPiece*>(spaces[newPosition[0]][newPosition[1] + 1].getPiecePtr());
				if (enPassantPawn)
				{
					if (enPassantPawn->isEnPassant())
					{
						spaces[newPosition[0]][newPosition[1] + 1].setPiecePtr(nullptr);
						removePiece(enPassantPawn);
					}
				}
			}
		}
	}
	else if (pieceToMove->getDisplayedChar() == 'K')
	{
		// Check if move was castle move
		int castleX = newPosition[0] - pieceToMove->getPosition()[0];
		// Castling
		if (abs(castleX) == 2)
		{
			if (castleX > 0)
			{
				Piece* rightRook = spaces[BOARD_SIZE - 1][pieceToMove->getPosition()[1]].getPiecePtr();
				vector<int> rookNewPosition = { rightRook->getPosition()[0] - 2, rightRook->getPosition()[1] };
				rightRook->move(spaces, rookNewPosition);
			}
			else if (castleX < 0)
			{
				Piece* leftRook = spaces[0][pieceToMove->getPosition()[1]].getPiecePtr();
				vector<int> rookNewPosition = { leftRook->getPosition()[0] + 3, leftRook->getPosition()[1] };
				leftRook->move(spaces, rookNewPosition);
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

vector<string> Board::getMoveHistory()
{
	return moveHistory;
}

bool Board::isCheck()
{
	return check;
}

bool Board::isCheckmate()
{
	return checkmate;
}

chrono::duration<double> Board::setTime(int color)
{
	chrono::duration<double> time = chrono::system_clock::now() - startTime;
	if (color == 0)
	{
		whiteTime += time;
	}
	else
	{
		blackTime += time;
	}
	startTime = chrono::system_clock::now();
	return time;
}

chrono::duration<double> Board::getTime(int color)
{
	if (color == 0)
	{
		return whiteTime;
	}
	else
	{
		return blackTime;
	}
}
