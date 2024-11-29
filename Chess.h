#pragma once
class Board;
class Piece;
class Player;
#include"utility.h"

class Chess
{
	int sr, sc, dr, dc;
	int t;
	Player* p[2];
	Board* b;
public:
	Chess();
	void play();
	void displayturnmsg(Player* Ap);
	void selectpiece();
	void selectdestination();
	bool validstartselection(Player* Ap, int r, int c);
	bool validendselection(Player* Ap, int r, int c);
	bool isCheck(color kingColor);
	bool isCheckmate(color kingColor);
	void makeMove(int startRow, int startCol, int endRow, int endCol, Piece* capturedPiece);
	void undoMove(int startRow, int startCol, int endRow, int endCol, Piece* capturedPiece);
};

 