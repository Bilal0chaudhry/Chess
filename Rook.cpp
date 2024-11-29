#include "Rook.h"
#include <iostream>
using namespace std;

Rook::Rook(Board* b, int r, int c, color _C) : Piece(b, r, c, _C)
{

}

char Rook::display()
{
    if ((r == 0 && (c == 0|| c == 7))|| (r == 7 && (c == 0|| c == 7)))
    {
        if (pieceColor == White)
        {
            return 'r';
        }
        else
        {
            return 'R';
        }
    }
}

bool Rook::ismovevalid(int startrow, int startcol, int destrow, int destcol)
{
    if (ishorizontalmove(startrow, startcol, destrow, destcol) && ishorizontalpathclear(b, startrow, startcol, destrow, destcol))
    {
        return true;
    }
    else if (isverticalmove(startrow, startcol, destrow, destcol) && isverticalpathclear(b, startrow, startcol, destrow, destcol))
    {
        return true;
    }                                                 
    return false; 
}


char Rook::getSymbol()
{
    if (pieceColor == White)
    {
        return 'r';
    }
    else
    {
        return 'R';
    }
}