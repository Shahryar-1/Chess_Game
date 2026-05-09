#include "bishop.h"

Bishop::Bishop(char color, int x, int y)
    : Piece(color, x, y) {
}

// Returns bishop symbol
char Bishop::getsymbol() const
{
    // White bishop
    if (color == 'W')
        return 'B';

    // Black bishop
    return 'b';
}


// Checks if bishop move is valid
bool Bishop::isvalidmove(int toX, int toY,
    Piece* board[8][8])
{
    // Bishop moves diagonally
    int dx = toX - x;
    int dy = toY - y;

    // Absolute values must be equal
    if (abs(dx) != abs(dy))
    {
        return false;
    }

    // Determine movement direction
    int stepX;
    int stepY;

    // Horizontal direction
    if (dx > 0)
        stepX = 1;
    else
        stepX = -1;

    // Vertical direction
    if (dy > 0)
        stepY = 1;
    else
        stepY = -1;

    // Check path for obstacles
    int currentX = x + stepX;
    int currentY = y + stepY;

    while (currentX != toX && currentY != toY)
    {
        if (board[currentX][currentY] != nullptr)
        {
            return false;
        }

        currentX += stepX;
        currentY += stepY;
    }

    // Cannot capture own piece
    if (board[toX][toY] != nullptr &&
        board[toX][toY]->getcolor() == color)
    {
        return false;
    }

    return true;
}
