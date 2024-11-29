#include "Bishop.h"
#include <iostream>
using namespace std;

Bishop::Bishop(Board* b, int r, int c, color _C) : Piece(b, r, c, _C)
{

}

char Bishop::display()
{
    if ((r == 0 && (c == 2 || c == 5)) || (r == 7 && (c == 2 || c == 5)))
    {
        if (pieceColor == White)
        {
            return 'b';
        }
        else
        {
            return 'B';
        }
    }
}

bool Bishop::ismovevalid(int startrow, int startcol, int destrow, int destcol)
{
    if (isdiagonalmove(startrow, startcol, destrow, destcol))
    {
        if (isdiagonalpathclear(b, startrow, startcol, destrow, destcol))
        {
            return true;
        }
    }
    return false;
}

char Bishop::getSymbol()
{
    if (pieceColor == White)
    {
        return 'b';
    }
    else
    {
        return 'B';
    }
}