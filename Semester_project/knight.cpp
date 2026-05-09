#include "knight.h"

Knight::Knight(char color, int x, int y) : Piece(color, x, y) {}

// returns symbol of knight
char Knight::getsymbol() const
{
    if (color == 'W')
    {
        return 'N';
    }

    return 'n';
}

bool Knight::isvalidmove(int toX, int toY, Piece* board[8][8])
{
    // Knight moves in L-shape
    int dx = abs(toX - x);
    int dy = abs(toY - y);
    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2)))
    {
        return false;
    }
    // Cannot capture own piece
    if (board[toX][toY] != nullptr &&
        board[toX][toY]->getcolor() == color)
    {
        return false;
    }
    return true;
}