#include "Queen.h"
#include <iostream>
using namespace std;

Queen::Queen(Board* b, int r, int c, color _C) : Piece(b, r, c, _C)
{

}

char Queen::display()
{
    if ((r == 0 || r == 7) && c == 3 )
    {
        if (pieceColor == White)
        {
            return 'q';
        }
        else
        {
            return 'Q';
        }
    }
}

bool Queen::ismovevalid(int startrow, int startcol, int destrow, int destcol)
{
    if (ishorizontalmove(startrow, startcol, destrow, destcol) && ishorizontalpathclear(b, startrow, startcol, destrow, destcol))
    {
        return true;
    }
    if (isverticalmove(startrow, startcol, destrow, destcol) && isverticalpathclear(b, startrow, startcol, destrow, destcol))
    {
        return true;
    }
    if (isdiagonalmove(startrow, startcol, destrow, destcol) && isdiagonalpathclear(b, startrow, startcol, destrow, destcol))
    {
        return true;
    }
    return false;
}



char Queen::getSymbol()
{
    if (pieceColor == White)
    {
        return 'q';
    }
    else
    {
        return 'Q';
    }
}