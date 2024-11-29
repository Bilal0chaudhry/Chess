#include "King.h"
#include <iostream>
using namespace std;

King::King(Board* b, int r, int c, color _C) : Piece(b, r, c, _C)
{

}

char King::display()
{
    if ((r == 0 || r == 7) && c == 4)
    {
        if (pieceColor == White)
        {
            return 'k';
        }
        else
        {
            return 'k';
        }
    }
}

bool King::ismovevalid(int startrow, int startcol, int destrow, int destcol)
{
    int rowDiff = abs(destrow - startrow);
    int colDiff = abs(destcol - startcol);
    if ((rowDiff <= 1) && (colDiff <= 1))
    {
        return true;
    }
    return false;
}

char King::getSymbol()
{
    if (pieceColor == White)
    {
        return 'k';
    }
    else
    {
        return 'K';
    }
}