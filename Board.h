#pragma once
#include"utility.h"
class Piece;

class Board 
{
    Piece*** p;
    int backgroundColors[8][8]; 
public:
    Board();
    void print();
    Piece* getpiece(int r, int c);
    void movePiece(int startRow, int startCol, int destRow, int destCol);
    void updatePosition(int srow, int scol, int drow, int dcol);
    int getBoxBackgroundColor(int row, int col);
    color getPieceColor(int row, int col);
    void setPieceBackground(int row, int col, int backgroundColor);
    void resetPieceBackground(int row, int col);
    void setPiece(int row, int col, Piece* piece);
};
