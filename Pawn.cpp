#include "Pawn.h"
#include <iostream>
#include"Board.h"
using namespace std;

Pawn::Pawn(Board* b, int r, int c, color _C) : Piece(b, r, c, _C) 
{

}

char Pawn::display()
{
    if (r == 1 || r == 6) 
    {
        if (pieceColor == White)
        {
            return 'p';
        }
        else 
        {
            return 'P';
        }
    }
}

bool Pawn::isFirstMove(int startrow) const
{
    if ((pieceColor == White && startrow == 6) || (pieceColor == Black && startrow == 1))
    {
        return true;
    }
    return false;
}


bool Pawn::ismovevalid(int startrow, int startcol, int destrow, int destcol)
{
    int direction = (getcolor() == White) ? -1 : 1;

    if (isFirstMove(startrow))
    {
        if ((destrow == startrow + direction || destrow == startrow + 2 * direction) && isverticalmove(startrow, startcol, destrow, destcol))
        {
            if (isverticalpathclear(b, startrow, startcol, destrow, destcol))
            {
                if (b->getpiece(destrow, destcol) == nullptr)
                {
                    return true;
                }
            }
        }
    }
    else
    {
        if (destrow == startrow + direction && isverticalmove(startrow, startcol, destrow, destcol))
        {
            if (isverticalpathclear(b, startrow, startcol, destrow, destcol) && b->getpiece(destrow, destcol) == nullptr)
            {
                return true;
            }
        }
    }

    if (isdiagonalmove(startrow, startcol, destrow, destcol))
    {
        if (abs(destrow - startrow) == 1 && abs(destcol - startcol) == 1)
        {
            Piece* destPiece = b->getpiece(destrow, destcol);
            if (destPiece != nullptr && destPiece->getcolor() != getcolor())
            {
                return true;
            }
        }
    }

    return false;
}

char Pawn::getSymbol()
{
    if (pieceColor == White) 
    {
        return 'p'; 
    }
    else 
    {
        return 'P';
    }
}