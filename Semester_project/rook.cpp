#include "rook.h"

Rook::Rook(char color, int x, int y)
    : Piece(color, x, y) {
}


// Returns symbol of rook
char Rook::getsymbol() const
{
    // Uppercase for White
    // Lowercase for Black
    if (color == 'W')
        return 'R';

    return 'r';
}


// Checks if rook move is valid
bool Rook::isvalidmove(int toX, int toY,
    Piece* board[8][8])
{
    // Rook moves only horizontally or vertically
    if (x != toX && y != toY)
    {
        return false;
    }

    // Moving vertically
    if (y == toY)
    {
        // Moving downward
        if (toX > x)
        {
            for (int i = x + 1; i < toX; i++)
            {
                if (board[i][y] != nullptr)
                {
                    return false;
                }
            }
        }

        // Moving upward
        else
        {
            for (int i = x - 1; i > toX; i--)
            {
                if (board[i][y] != nullptr)
                {
                    return false;
                }
            }
        }
    }

    // Moving horizontally
    if (x == toX)
    {
        // Moving right
        if (toY > y)
        {
            for (int i = y + 1; i < toY; i++)
            {
                if (board[x][i] != nullptr)
                {
                    return false;
                }
            }
        }

        // Moving left
        else
        {
            for (int i = y - 1; i > toY; i--)
            {
                if (board[x][i] != nullptr)
                {
                    return false;
                }
            }
        }
    }

    // Cannot capture own piece
    if (board[toX][toY] != nullptr &&
        board[toX][toY]->getcolor() == color)
    {
        return false;
    }

    return true;
}