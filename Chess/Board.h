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

class Board
{
	const int BOARD_DISPLAY_MAGNITUDE = 5; // Odd number only
	BoardSpace spaces[Globals::BOARD_SIZE][Globals::BOARD_SIZE];
	std::vector<Piece*> whitePieces;
	std::vector<PawnPiece*> whitePawns;
	std::vector<Piece*> blackPieces;
	std::vector<PawnPiece*> blackPawns;
	KingPiece* blackKing;
	bool check;
	bool checkmate;
	std::vector<std::string> moveHistory;
	void loadBoardFromString(std::string board[Globals::BOARD_SIZE][Globals::BOARD_SIZE]);
	void clearBoard();
	bool checkForCheckmate(int player);
	void removePiece(Piece* piece);
	Piece* promotePawn(Piece* pawn);
	std::vector<PawnPiece*> getPawns(int color);

public:
	Board();

	void printBoard(int color);
	void getPieceMoves(std::vector<int> piecePosition);
	std::vector<std::string> getMoveHistory();
	bool attemptPieceMove(std::vector<int> pieceToMovePosition, int player, std::vector<int> destination);
	void movePiece(Piece* pieceToMove, std::vector<int> newPosition);
	bool willPutInCheck(Piece* pieceToMove, std::vector<int> destination);
	std::vector<Piece*> getPieces(int color);
	void addPiece(Piece* piece);
	void checkAllColorPieceMoves(int color);
	void saveGame(int* player);
	void loadGame(int* player);
	bool isCheck();
	bool isCheckmate();
	void clearEnPassant(int color);
};