#include "Piece.h"
#include"Board.h"
#include <iostream>
using namespace std;

Piece::Piece(Board* _b,int _r, int _c, color co)
{
    this->b = _b;
    this->r = _r;
    this->c = _c;
    this->pieceColor = co;
}

color Piece::getcolor()
{
    return pieceColor;
}

bool Piece::ishorizontalmove(int sr, int sc, int er, int ec)
{
    return sr == er;
}

bool    Piece::isverticalmove(int sr, int sc, int er, int ec)
{
    return sc == ec;
}

bool Piece::isdiagonalmove(int sr, int sc, int er, int ec)
{
    int rowDiff = abs(sr - er);
    int colDiff = abs(sc - ec);
    return rowDiff == colDiff;
}

bool Piece::ishorizontalpathclear(Board* b, int sr, int sc, int er, int ec)
{
    if (sc < ec)
    {
        for (int c = sc + 1; c < ec; c++)
        {
            if (b->getpiece(sr, c) != nullptr)
            {
                return false; 
            }
        }
    }
    else if (sc > ec)
    {
        for (int c = ec + 1; c < sc; c++)
        {
            if (b->getpiece(sr, c) != nullptr)
            {
                return false; 
            }
        }
    }
    return true; 
}


bool Piece::isverticalpathclear(Board* b, int sr, int sc, int er, int ec)
{
    if (sr < er)
    {
        for (int r = sr + 1; r < er; r++)
        {
            if (b->getpiece(r, sc) != nullptr)
            {
                return false;
            }
        }
    }
    else if (sr > er)
    {
        for (int r = er + 1; r < sr; r++)
        {
            if (b->getpiece(r, sc) != nullptr)
            {
                return false;
            }
        }
    }
    return true;
}

bool Piece::isdiagonalpathclear(Board* b, int sr, int sc, int er, int ec)
{
    int dr = (er > sr) ? 1 : -1;
    int dc = (ec > sc) ? 1 : -1;

    for (int r = sr + dr, c = sc + dc; r != er; r += dr, c += dc)
    {
        Piece* piece = b->getpiece(r, c);
        if (piece != nullptr)
        {
            return false;
        }
    }
    return true;
}

