#pragma once
#include"utility.h"
class Board;

class Piece 
{ 
protected:
    Board *b;
    int r, c;
    color pieceColor;
public:
    Piece(Board* _b, int _r, int _c, color co);
    virtual char display() = 0;
    color getcolor();
    virtual bool ismovevalid(int startrow, int startcol, int destrow, int destcol) = 0;
    virtual char getSymbol() = 0;
    bool ishorizontalmove(int sr, int sc, int er, int ec);
    bool isverticalmove(int sr, int sc, int er, int ec);
    bool isdiagonalmove(int sr, int sc, int er, int ec);
    bool ishorizontalpathclear(Board* b, int sr, int sc, int er, int ec);
    bool isverticalpathclear(Board* b, int sr, int sc, int er, int ec);
    bool isdiagonalpathclear(Board* b, int sr, int sc, int er, int ec);
};
