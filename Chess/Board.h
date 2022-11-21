#pragma once
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

class Board
{
	const int BOARD_DISPLAY_MAGNITUDE = 5; // Odd number only
	BoardSpace spaces[Globals::BOARD_SIZE][Globals::BOARD_SIZE];
	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;
	void loadBoardFromString(std::string board[Globals::BOARD_SIZE][Globals::BOARD_SIZE]);
	void clearBoard();

public:
	Board();

	void printBoard(int color);
	void getPieceMoves(std::vector<int> piecePosition);
	bool attemptPieceMove(std::vector<int> pieceToMovePosition, int player, std::vector<int> destination);
	void movePiece(Piece* pieceToMove, std::vector<int> newPosition);
	std::vector<Piece*> getPieces(int color);
	void checkAllColorPieceMoves(int color);
	void saveGame(int* player);
	void loadGame(int* player);
};