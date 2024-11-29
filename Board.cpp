#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include"Knight.h"
#include"Bishop.h"
#include"Piece.h"
#include"King.h"
#include"Queen.h"
#include<iostream>
#include <windows.h>
#include"utility.h"
#include <stdio.h>
using namespace std;

Piece* Board::getpiece(int r, int c)
{
    return p[r][c];
}

Board::Board() 
{
    p = new Piece * *[8];
    for (int i = 0; i < 8; i++)
    {
        p[i] = new Piece * [8];
        for (int j = 0; j < 8; j++) 
        {
            if (i == 1) 
            {
                p[i][j] = new Pawn(this, i, j, Black); 
            }
            else if (i == 6) 
            {
                p[i][j] = new Pawn(this, i, j, White);
            }
            else if (i == 0 && (j == 0 || j == 7))
            {
                p[i][j] = new Rook(this, i, j, Black);
            }
            else if (i == 7 && (j == 0 || j == 7))
            {
                p[i][j] = new Rook(this, i, j, White);
            }
            else if (i == 0 && (j == 1 || j == 6))
            {
                p[i][j] = new Knight(this, i, j, Black);
            }
            else if (i == 7 && (j == 1 || j == 6))
            {
                p[i][j] = new Knight(this, i, j, White);
            }
            else if (i == 0 && (j == 2 || j == 5))
            {
                p[i][j] = new Bishop(this, i, j, Black);
            }
            else if (i == 7 && (j == 2 || j == 5))
            {
                p[i][j] = new Bishop(this, i, j, White);
            }
            else if (i == 0 && j == 4)
            {
                p[i][j] = new King(this, i, j, Black);
            }
            else if (i == 7 && j == 4)
            {
                p[i][j] = new King(this, i, j, White);
            }
            else if (i == 0 && j == 3)
            {
                p[i][j] = new Queen(this, i, j, Black);
            }
            else if (i == 7 && j == 3)
            {
                p[i][j] = new Queen(this, i, j, White);
            }
            else 
            {
                p[i][j] = nullptr;
            }
        }
    }
}

#include <iostream>
#include <windows.h>

const wchar_t* getUnicodePiece(char letter) {
    switch (letter) {
    case 'p': return L" ♙ "; // Black Pawn
    case 'n': return L" ♘ "; // Black Knight
    case 'b': return L" ♗ "; // Black Bishop
    case 'r': return L" ♖ "; // Black Rook
    case 'q': return L" ♕ "; // Black Queen
    case 'k': return L" ♔ "; // Black King
    case 'P': return L" ♟ "; // White Pawn
    case 'N': return L" ♞ "; // White Knight
    case 'B': return L" ♝ "; // White Bishop
    case 'R': return L" ♜ "; // White Rook
    case 'Q': return L" ♛ "; // White Queen
    case 'K': return L" ♚ "; // White King
    default: return L" - "; // Empty square
    }
}

void print_piece_picture(char letter)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;

    const wchar_t* piece = getUnicodePiece(letter);
    WriteConsoleW(handle, piece, wcslen(piece), &written, NULL);
}

void Board::print()
{
    system("cls");

    int startX = 0;
    int startY = 0;

    for (int i = 0; i < 8; i++)
    {
        COORD position;
        position.Y = startY + i;
        position.X = startX;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }

            if (p[i][j] == nullptr)
            {
                std::cout << " - ";
            }
            else
            {
                char piece = p[i][j]->display();
                print_piece_picture(piece);
            }
        }
        std::cout << std::endl;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void Board::setPiece(int row, int col, Piece* piece)
{
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        p[row][col] = piece;
    }
}


void Board::movePiece(int startRow, int startCol, int destRow, int destCol)
{
    Piece* pieceToMove = p[startRow][startCol];
    p[destRow][destCol] = pieceToMove;
    p[startRow][startCol] = nullptr; 
}

int Board::getBoxBackgroundColor(int row, int col)
{
    if ((row + col) % 2 == 0)
    {
        return 240; 
    }
    else
    {
        return 15; 
    }
}

void Board::updatePosition(int srow, int scol, int drow, int dcol)
{
    int startX = 0;
    int startY = 0;
    int boxWidth = 3;

    int sourceBgColor = getBoxBackgroundColor(srow, scol);
    int destBgColor = getBoxBackgroundColor(drow, dcol);

    int consoleSX = startX + (scol * boxWidth);
    int consoleSY = startY + srow;

    int consoleDX = startX + (dcol * boxWidth);
    int consoleDY = startY + drow;

    gotoRowCol(consoleSY, consoleSX);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), sourceBgColor);

    if (p[srow][scol] == nullptr)
    {
        cout << " - ";
    }
    else
    {
        char piece = p[srow][scol]->display();
        print_piece_picture(piece);
    }

    gotoRowCol(consoleDY, consoleDX);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), destBgColor);
    if (p[drow][dcol] == nullptr)
    {
        cout << " - ";
    }
    else
    {
        char piece = p[drow][dcol]->display();
        print_piece_picture(piece);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    gotoRowCol(10, 0);
}

color Board::getPieceColor(int row, int col)
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8) 
    {
        return color::NoColor; 
    }

    p[row][col] = getpiece(row, col);
    Piece* piece = p[row][col];
    if (piece != nullptr) 
    {
        return piece->getcolor(); 
    }
    return color::NoColor;
}

void Board::setPieceBackground(int row, int col, int backgroundColor)
{
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        backgroundColors[row][col] = backgroundColor;
    }
}

void Board::resetPieceBackground(int row, int col)
{
    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        backgroundColors[row][col] = 15; 
    }
}
