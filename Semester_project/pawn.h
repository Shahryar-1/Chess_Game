#pragma once
#include "piece.h"
#include "rook.h"
class Pawn : public Piece
{
public:
    // Constructor
    Pawn(char color, int x, int y);

    // Checks if pawn move is valid
    bool isvalidmove(int toX, int toY,
        Piece* board[8][8]) override;

    // Returns symbol of pawn
    char getsymbol() const override;
};
