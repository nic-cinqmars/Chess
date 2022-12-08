#pragma once
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include "BoardSpace.h"
#include "PawnPiece.h"
#include "RookPiece.h"
#include "KnightPiece.h"
#include "BishopPiece.h"
#include "QueenPiece.h"
#include "KingPiece.h"
#include "Globals.h"
#include "invalid_move.h"
#include <chrono>

// Board stores the spaces on the board itself aswell as data that is useful for logic of the chess game
class Board
{
	// Changes how big the board is displayed in the console. Only works with odd numbers.
	const int BOARD_DISPLAY_MAGNITUDE = 5;

	// Array containing each space on the board
	BoardSpace spaces[Globals::BOARD_SIZE][Globals::BOARD_SIZE];

	std::vector<Piece*> whitePieces;
	std::vector<PawnPiece*> whitePawns;
	std::vector<Piece*> blackPieces;
	std::vector<PawnPiece*> blackPawns;

	bool check;
	bool checkmate;
	bool stalemate;

	std::vector<std::string> moveHistory;

	std::chrono::system_clock::time_point startTime;
	std::chrono::duration<double> whiteTime;
	std::chrono::duration<double> blackTime;

	// Loads the pieces onto the board spaces from a 2D string array.
	void loadBoardFromString(std::string board[Globals::BOARD_SIZE][Globals::BOARD_SIZE]);

	// Create a new board with default values.
	void createNewBoard();

	// Initializes the spaces on the board in a checkerboard pattern.
	void initializeBoardSpaces();

	// Adds a piece to its corresponding vector(s).
	void addPiece(Piece* piece);

	// Removes a piece from its corresponding vector(s).
	void removePiece(Piece* piece);

	// Returns the Piece* vector of the specified color
	std::vector<Piece*> getPieces(int color);

	// Returns the PawnPiece* vector of the corresponding color.
	std::vector<PawnPiece*> getPawns(int color);

	// Checks if a piece's move will put the player in check.
	bool willPutInCheck(Piece* pieceToMove, std::vector<int> destination);

	// Moves a piece to a new position on the board.
	void movePiece(Piece* pieceToMove, std::vector<int> newPosition);

	// Returns the piece that a player wants to promote a pawn to.
	Piece* promotePawn(Piece* pawn);

	// Checks if the specified player has any legal moves.
	// Used for checking for a checkmate or stalemate.
	bool checkForAnyMove(int player);

public:
	// Creates a new Board object with a default chess board and default values.
	Board();

	// Loads the game from the game.txt file.
	// If the game.txt file doesn't exist, it loads a default game.
	void loadGame(int* player);

	// Saves the game to a game.txt file.
	void saveGame(int* player);

	// Clears the value of enPassant for pawns of a certain color.
	void clearEnPassant(int color);

	// Prints the board to the console in the orientation of the specified color.
	void printBoard(int color);

	// Tries to move a player's piece.
	// If the move does not work, an invalid_move exception is thrown.
	// If the move does work, the function movePiece is called.
	void attemptPieceMove(std::vector<int> pieceToMovePosition, int player, std::vector<int> destination);

	// Returns the string vector containing the history of the moves played in the game.
	std::vector<std::string> getMoveHistory();

	// Returns the value of check variable.
	bool isCheck();

	// Returns the value of the checkmate variable.
	bool isCheckmate();

	// Returns the value of the stalemate variable.
	bool isStalemate();

	// Adds the time it took for a player to make their move and returns it.
	std::chrono::duration<double> setTime(int color);

	// Returns the time spent by a player to make their moves.
	std::chrono::duration<double> getTime(int color);
};