#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King(Board* b, int r, int c, color _C);
	virtual char display();
	virtual bool ismovevalid(int startrow, int startcol, int destrow, int destcol);
	virtual char getSymbol();
};

