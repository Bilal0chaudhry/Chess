#include "Knight.h"
#include <iostream>
using namespace std;

Knight::Knight(Board* b, int r, int c, color _C) : Piece(b, r, c, _C)
{

}
char Knight::display()
{
    if ((r == 0 && (c == 1||c == 6)) || (r == 7 && (c == 1||c == 6)))
    {
        if (pieceColor == White)
        {
            return 'n';
        }
        else
        {
            return 'N';
        }
    }
} 

bool Knight::ismovevalid(int startrow, int startcol, int destrow, int destcol)
{
    int rowDiff = abs(destrow - startrow);
    int colDiff = abs(destcol - startcol);
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))
    {
        return true;
    }
    return false;
}

char Knight::getSymbol()
{
    if (pieceColor == White)
    {
        return 'n';
    }
    else
    {
        return 'N';
    }
}