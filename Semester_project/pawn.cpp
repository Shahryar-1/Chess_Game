#include "pawn.h"

Pawn::Pawn(char color, int x, int y)
    : Piece(color, x, y)
{
}


// Returns symbol of pawn
char Pawn::getsymbol() const
{
    // Uppercase for White
    // Lowercase for Black
    if (color == 'W')
        return 'P';

    return 'p';
}


// Checks if pawn move is valid
bool Pawn::isvalidmove(int toX, int toY,
    Piece* board[8][8])
{
    // White pawn moves upward
    if (color == 'W')
    {
        // One step forward
        if (toX == x - 1 && toY == y && board[toX][toY] == nullptr)
        {
            return true;
        }

        // First move can move two steps
        if (x == 6 && toX == x - 2 && toY == y &&
            board[x - 1][y] == nullptr &&
            board[toX][toY] == nullptr)
        {
            return true;
        }

        // Diagonal capture
        if (toX == x - 1 &&
            (toY == y - 1 || toY == y + 1) &&
            board[toX][toY] != nullptr &&
            board[toX][toY]->getcolor() != color)
        {
            return true;
        }
    }

    // Black pawn moves downward
    else
    {
        // One step forward
        if (toX == x + 1 &&
            toY == y &&
            board[toX][toY] == nullptr)
        {
            return true;
        }

        // First move can move two steps
        if (x == 1 &&
            toX == x + 2 &&
            toY == y &&
            board[x + 1][y] == nullptr &&
            board[toX][toY] == nullptr)
        {
            return true;
        }

        // Diagonal capture
        if (toX == x + 1 &&
            (toY == y - 1 || toY == y + 1) &&
            board[toX][toY] != nullptr &&
            board[toX][toY]->getcolor() != color)
        {
            return true;
        }
    }

    // Invalid move
    return false;
}