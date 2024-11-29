#include "Chess.h"
#include"Player.h"
#include"Board.h"
#include"Piece.h"
#include<time.h>
#include<string.h>
#include<iostream>
#include <chrono> 
#include <thread> 

using namespace std;

Chess::Chess()
{
	p[0] = new Player("BLACK", Black);
	p[1] = new Player("WHITE", White);
	b = new Board();
	srand(time(0));
	t = rand() % 2;
}

void Chess::displayturnmsg(Player* Ap)
{
	cout << Ap->getname() << "'s Turn\n";
}

void Chess::selectpiece()
{
	cin >> sr >> sc;
}

void Chess::selectdestination()
{
	cin >> dr >> dc;
}

bool Chess::validstartselection(Player* Ap, int r, int c)
{
	if ((r < 0 || r >= 8) || (c < 0 || c >= 8))
	{
		return false;
	}
	Piece* p = b->getpiece(r, c);

	return p != nullptr && p->getcolor() == Ap->getcolor();
}

bool Chess::validendselection(Player* Ap, int r, int c)
{
    if ((r < 0 || r >= 8) || (c < 0 || c >= 8))
    {
        return false;
    }

    Piece* endPiece = b->getpiece(r, c);

    if (!b->getpiece(sr,sc)->ismovevalid(sr, sc, r, c))
    { 
        return false; 
    }

    if (endPiece != nullptr)
    {
        if (endPiece->getcolor() == Ap->getcolor()) 
        {
            return false;
        }
    }

    return true; 
}

void clearmessage()
{
    int clearStartRow = 9;
    int clearEndRow = 20;
    int clearStartCol = 0;
    int clearEndCol = 50;

    for (int i = clearStartRow; i < clearEndRow; ++i) {
        gotoRowCol(i, clearStartCol);
        cout << string(clearEndCol - clearStartCol, ' '); 
    }
}

bool Chess::isCheck(color kingColor)
{
    int kingRow = -1, kingCol = -1;
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece* piece = b->getpiece(row, col);
            if (piece != nullptr && ((piece->getSymbol() == 'k' && kingColor == White) || (piece->getSymbol() == 'K' && kingColor == Black)))
            {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1 && kingCol != -1)
            break;
    }

    if (kingRow == -1 || kingCol == -1)
        return false;
    for (int row = 0; row < 8; ++row) 
    {
        for (int col = 0; col < 8; ++col) 
        {
            Piece* piece = b->getpiece(row, col);
            if (piece == nullptr || piece->getcolor() == kingColor) 
            {
                continue;
            }

            if (piece->ismovevalid(row, col, kingRow, kingCol)) 
            {
                return true;
            }
        }
    }

    return false; 
}

void Chess::makeMove(int startRow, int startCol, int endRow, int endCol, Piece* capturedPiece) {
    b->movePiece(startRow, startCol, endRow, endCol);
    b->setPiece(endRow, endCol, capturedPiece);
}

void Chess::undoMove(int startRow, int startCol, int endRow, int endCol, Piece* capturedPiece) {
    b->movePiece(endRow, endCol, startRow, startCol);
    b->setPiece(endRow, endCol, capturedPiece);
}

bool Chess::isCheckmate(color kingColor) 
{
    int kingRow = -1, kingCol = -1;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* piece = b->getpiece(row, col);
            if (piece != nullptr && ((piece->getSymbol() == 'k' && kingColor == White) || (piece->getSymbol() == 'K' && kingColor == Black))) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    if (kingRow == -1 || kingCol == -1) return false; 

    int moves[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
    for (int i = 0; i < 8; ++i) {
        int newRow = kingRow + moves[i][0];
        int newCol = kingCol + moves[i][1];
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            Piece* target = b->getpiece(newRow, newCol);
            if (target == nullptr || target->getcolor() != kingColor) 
            {
                Piece* original = b->getpiece(newRow, newCol);
                b->setPiece(newRow, newCol, b->getpiece(kingRow, kingCol));
                b->setPiece(kingRow, kingCol, nullptr);
                bool stillInCheck = false;
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        Piece* piece = b->getpiece(row, col);
                        if (piece == nullptr || piece->getcolor() == kingColor) continue;
                        if (piece->ismovevalid(row, col, newRow, newCol)) {
                            stillInCheck = true;
                            break;
                        }
                    }
                    if (stillInCheck) break;
                }

                b->setPiece(kingRow, kingCol, b->getpiece(newRow, newCol));
                b->setPiece(newRow, newCol, original);

                if (!stillInCheck) return false; 
            }
        }
    }

    return true; 
}




void Chess::play()
{
    b->print();
    while (true)
    {
        gotoRowCol(9, 0);
        displayturnmsg(p[t]);
        int startRow, startCol;
        cout << "Select a piece (row column): " << endl;
        getrowcolbyleftclick(startRow, startCol);
        if (!validstartselection(p[t], startRow, startCol))
        {
            continue;
        }
        sr = startRow;
        sc = startCol;
        int destRow, destCol;
        cout << "select a destination (row column): " << endl;
        getrowcolbyleftclick(destRow, destCol);
        if (!validendselection(p[t], destRow, destCol))
        {
            continue;
        }

        b->movePiece(startRow, startCol, destRow, destCol);
        b->updatePosition(startRow, startCol, destRow, destCol);
        t = (t + 1) % 2;

        if (isCheck(p[t]->getcolor()))
        {   
            clearmessage();
            gotoRowCol(9, 0);
            cout << "Check on Opponent king!!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            clearmessage();

            if (isCheckmate(p[t]->getcolor()))
            {
                clearmessage();
                gotoRowCol(9, 0);
                cout << "Checkmate! Game Over!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                clearmessage();
                exit(0);
            }
            continue;
        }
        clearmessage();
        if (isCheck(p[(t + 1) % 2]->getcolor()))
        {
            clearmessage();
            gotoRowCol(9, 0);
            cout << "Your King is in Check!!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            b->movePiece(destRow, destCol, startRow, startCol);
            b->updatePosition(destRow, destCol, startRow, startCol);
            t = (t + 1) % 2;
            clearmessage();
            continue; 
        }
    }
}



