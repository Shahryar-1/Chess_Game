#include "queen.h"

//Queen constructor
Queen::Queen(char color, int x, int y) : Piece(color, x, y) {}

// checks if queen move is valid
bool Queen::isvalidmove(int toX, int toY, Piece* board[8][8])
{
    int dx = toX - x;
    int dy = toY - y;

    // Vertical Movement
    if (y == toY)
    {
        int step;

        if (toX > x)
        {
            step = 1;
        }
        else
        {
            step = -1;
        }

        // Check path
        for (int i = x + step; i != toX; i += step)
        {
            if (board[i][y] != nullptr)
            {
                return false;
            }
        }

        // Own piece check
        if (board[toX][toY] != nullptr &&
            board[toX][toY]->getcolor() == color)
        {
            return false;
        }

        return true;
    }
    // Horizontal Movement
    if (x == toX)
    {
        int step;

        if (toY > y)
        {
            step = 1;
        }
        else
        {
            step = -1;
        }

        // Check path
        for (int i = y + step; i != toY; i += step)
        {
            if (board[x][i] != nullptr)
            {
                return false;
            }
        }

        // Own piece check
        if (board[toX][toY] != nullptr &&
            board[toX][toY]->getcolor() == color)
        {
            return false;
        }

        return true;
    }

    // Diagonal Movement
    if (abs(dx) == abs(dy))
    {
        int stepX;
        int stepY;

        if (dx > 0)
        {
            stepX = 1;
        }
        else
        {
            stepX = -1;
        }

        if (dy > 0)
        {
            stepY = 1;
        }
        else
        {
            stepY = -1;
        }

        int currentX = x + stepX;
        int currentY = y + stepY;

        // Check diagonal path
        while (currentX != toX && currentY != toY)
        {
            if (board[currentX][currentY] != nullptr)
            {
                return false;
            }

            currentX += stepX;
            currentY += stepY;
        }

        // Own piece check
        if (board[toX][toY] != nullptr &&
            board[toX][toY]->getcolor() == color)
        {
            return false;
        }

        return true;
    }

    return false;
}

//This will return the color for the queen piece 
//if return Capital Q the Piece is White and if small q the piece is black
char Queen::getsymbol() const
{
    if (color == 'W')
    {
        return 'Q';
    }

    return 'q';
}