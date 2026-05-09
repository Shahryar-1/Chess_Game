#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
    Rook(char color, int x, int y);

    bool isvalidmove(int toX, int toY,
        Piece* board[8][8]) override;

    char getsymbol() const override;
};