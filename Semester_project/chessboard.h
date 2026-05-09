#pragma once
#include <iostream>
#include <windows.h>
#include "Piece.h"
using namespace std;

class ChessBoard
{
private:
    Piece* grid[8][8];

public:
    ChessBoard();
    ~ChessBoard();

    void   display();
    Piece* getPiece(int x, int y);
    bool   isInsideBoard(int x, int y);
    bool   movePiece(int fromX, int fromY,
        int toX, int toY,
        char currentTurn);
    bool   isKingAlive(char color);
};